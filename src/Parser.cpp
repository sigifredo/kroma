

// own
#include <Parser.hpp>
#include <IO.hpp>
#include <ParseError.hpp>

#include <expressions/AssignExpr.hpp>
#include <expressions/BinaryExpr.hpp>
#include <expressions/CallExpr.hpp>
#include <expressions/GetExpr.hpp>
#include <expressions/GroupingExpr.hpp>
#include <expressions/LiteralExpr.hpp>
#include <expressions/LogicalExpr.hpp>
#include <expressions/RangeExpr.hpp>
#include <expressions/UnaryExpr.hpp>
#include <expressions/VariableExpr.hpp>

#include <stmt/BlockStmt.hpp>
#include <stmt/ExpressionStmt.hpp>
#include <stmt/IfStmt.hpp>
#include <stmt/PrintStmt.hpp>
#include <stmt/VarStmt.hpp>

Parser::Parser(const std::vector<Token> &tokens) : tokens(tokens) {}

std::vector<std::unique_ptr<Stmt>> Parser::parse()
{
    std::vector<std::unique_ptr<Stmt>> statements;

    while (!isAtEnd())
    {
        if (auto stmt = declaration())
        {
            statements.push_back(std::move(stmt));
        }
    }

    return statements;
}

std::unique_ptr<Expr> Parser::assignment()
{
    auto expr = logicOr();

    if (match({TokenType::EQUAL}))
    {
        Token equals = previous();
        auto value = assignment();

        if (auto *varExpr = dynamic_cast<VariableExpr *>(expr.get()))
        {
            return std::make_unique<AssignExpr>(varExpr->name(), std::move(value));
        }

        error(equals, "Invalid assignment target.");
    }

    return expr;
}

std::unique_ptr<Expr> Parser::call()
{
    auto expr = primary();

    while (true)
    {
        if (match({TokenType::LEFT_PAREN}))
        {
            expr = finishCall(std::move(expr));
        }
        else if (match({TokenType::DOT}))
        {
            Token name = consume(TokenType::IDENTIFIER, "Expect property name after '.'.");
            expr = std::make_unique<GetExpr>(std::move(expr), name);
        }
        else
        {
            break;
        }
    }

    return expr;
}

std::unique_ptr<Expr> Parser::comparison()
{
    auto expr = range();

    while (match({TokenType::GREATER, TokenType::GREATER_EQUAL,
                  TokenType::LESS, TokenType::LESS_EQUAL}))
    {
        Token op = previous();
        auto right = range();
        expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::equality()
{
    auto expr = comparison();

    while (match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL}))
    {
        Token op = previous();
        auto right = comparison();
        expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::expression()
{
    return assignment();
}

std::unique_ptr<Expr> Parser::factor()
{
    auto expr = unary();

    while (match({TokenType::SLASH, TokenType::STAR}))
    {
        Token op = previous();
        auto right = unary();
        expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::finishCall(std::unique_ptr<Expr> callee)
{
    std::vector<std::unique_ptr<Expr>> arguments;

    if (!check(TokenType::RIGHT_PAREN))
    {
        do
        {
            arguments.push_back(expression());
        } while (match({TokenType::COMMA}));
    }

    Token paren = consume(TokenType::RIGHT_PAREN, "Expect ')' after arguments.");
    return std::make_unique<CallExpr>(std::move(callee), paren, std::move(arguments));
}

std::unique_ptr<Expr> Parser::fstring()
{
    Token fstringToken = previous();
    Value rawToken = fstringToken.literal();

    if (!rawToken.isString())
    {
        throw ParseError("Error en el formato de fstring");
    }

    std::string rawStr = rawToken.asString();
    std::vector<std::unique_ptr<Expr>> parts;
    std::string buffer;
    size_t i = 0;

    while (i < rawStr.length())
    {
        if (rawStr[i] == '{')
        {
            if (!buffer.empty())
            {
                parts.push_back(std::make_unique<LiteralExpr>(buffer));
                buffer.clear();
            }

            size_t start = ++i;
            int depth = 1;

            while (i < rawStr.length() && depth > 0)
            {
                if (rawStr[i] == '{')
                    depth++;
                else if (rawStr[i] == '}')
                    depth--;
                i++;
            }

            if (depth != 0)
            {
                throw ParseError("FString mal formado: llaves desbalanceadas.");
            }

            std::string exprSource = rawStr.substr(start, i - start - 1);
            auto exprTokens = scanInline(exprSource);
            Parser subparser(exprTokens);
            std::unique_ptr<Expr> expr = subparser.parse()[0];
            parts.push_back(std::move(expr));
        }
        else
        {
            buffer += rawStr[i++];
        }
    }

    if (!buffer.empty())
    {
        parts.push_back(std::make_unique<LiteralExpr>(buffer));
    }

    // Combinar todas las partes en BinaryExprs encadenadas con operador "+"
    if (parts.empty())
        return std::make_unique<LiteralExpr>("");

    std::unique_ptr<Expr> result = std::move(parts[0]);
    for (size_t j = 1; j < parts.size(); ++j)
    {
        result = std::make_unique<BinaryExpr>(std::move(result), Token(TokenType::PLUS, "+", std::monostate{}, fstringToken.line), std::move(parts[j]));
    }

    return result;
}

std::unique_ptr<Expr> Parser::logicAnd()
{
    auto expr = equality();

    while (match({TokenType::AND}))
    {
        Token op = previous();
        auto right = equality();
        expr = std::make_unique<LogicalExpr>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::logicOr()
{
    auto expr = logicAnd();

    while (match({TokenType::OR}))
    {
        Token op = previous();
        auto right = logicAnd();
        expr = std::make_unique<LogicalExpr>(std::move(expr), op, std::move(right));
    }
    return expr;
}

std::unique_ptr<Expr> Parser::primary()
{
    if (match({TokenType::FALSE}))
        return std::make_unique<LiteralExpr>(false);
    if (match({TokenType::TRUE}))
        return std::make_unique<LiteralExpr>(true);
    if (match({TokenType::_NULL}))
        return std::make_unique<LiteralExpr>(nullptr);
    if (match({TokenType::NUMBER, TokenType::STRING}))
        return std::make_unique<LiteralExpr>(previous().literal());
    if (match({TokenType::IDENTIFIER}))
        return std::make_unique<VariableExpr>(previous());
    if (match({TokenType::LEFT_PAREN}))
    {
        auto expr = expression();
        consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
        return std::make_unique<GroupingExpr>(std::move(expr));
    }

    throw ParseError("Expected expression.");
}

std::unique_ptr<Expr> Parser::range()
{
    auto start = term();

    if (match({TokenType::DOT_DOT}))
    {
        auto end = term();
        std::unique_ptr<Expr> step = nullptr;

        if (match({TokenType::BY}))
        {
            step = term();
        }

        return std::make_unique<RangeExpr>(std::move(start), std::move(end), std::move(step));
    }

    return start;
}

std::unique_ptr<Expr> Parser::term()
{
    auto expr = factor();

    while (match({TokenType::PLUS, TokenType::MINUS}))
    {
        Token op = previous();
        auto right = factor();
        expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::unary()
{
    if (match({TokenType::BANG, TokenType::MINUS}))
    {
        Token op = previous();
        auto right = unary();
        return std::make_unique<UnaryExpr>(op, std::move(right));
    }

    return call();
}

std::unique_ptr<Stmt> Parser::block()
{
    std::vector<std::unique_ptr<Stmt>> statements;

    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd())
    {
        if (auto decl = declaration())
        {
            statements.push_back(std::move(decl));
        }
    }

    consume(TokenType::RIGHT_BRACE, "Se esperaba '}' para cerrar el bloque.");

    return std::make_unique<BlockStmt>(std::move(statements));
}

std::unique_ptr<Stmt> Parser::declaration()
{
    try
    {
        if (match({TokenType::LET, TokenType::CONST}))
            return varDeclaration(previous());
        if (match({TokenType::PRINT}))
            return printStatement();
        if (match({TokenType::IF}))
            return ifStatement();
        if (match({TokenType::FUN}))
            ; // return funDeclaration();
        if (match({TokenType::CLASS}))
            ; // return classDeclaration();

        return statement();
    }
    catch (const ParseError &error)
    {
        std::cerr << error.what() << std::endl;
        synchronize();
        return nullptr;
    }
}

std::unique_ptr<Stmt> Parser::expressionStatement()
{
    auto expr = expression();
    consume(TokenType::SEMICOLON, "Expect ';' after expression.");
    return std::make_unique<ExpressionStmt>(std::move(expr));
}

std::unique_ptr<Stmt> Parser::ifStatement()
{
    consume(TokenType::LEFT_PAREN, "Expect '(' after 'if'.");
    auto condition = expression();
    consume(TokenType::RIGHT_PAREN, "Expect ')' after if condition.");

    auto thenBranch = statement();
    std::unique_ptr<Stmt> elseBranch = nullptr;

    if (match({TokenType::ELSE}))
    {
        elseBranch = statement();
    }

    return std::make_unique<IfStmt>(std::move(condition),
                                    std::move(thenBranch),
                                    std::move(elseBranch));
}

std::unique_ptr<Stmt> Parser::printStatement()
{
    auto value = expression();
    consume(TokenType::SEMICOLON, "Se esperaba ';' después de la expresión.");
    return std::make_unique<PrintStmt>(std::move(value));
}

std::unique_ptr<Stmt> Parser::statement()
{
    if (match({TokenType::LEFT_BRACE}))
        return block();
    if (match({TokenType::FOR}))
        ; // return forStatement();
    if (match({TokenType::IF}))
        ; // return ifStatement();
    if (match({TokenType::RETURN}))
        ; // return returnStatement();

    return expressionStatement();
}

std::unique_ptr<Stmt> Parser::varDeclaration(const Token &modifier)
{
    Token name = consume(TokenType::IDENTIFIER, "Expect variable name.");
    std::unique_ptr<Expr> initializer = nullptr;

    if (match({TokenType::EQUAL}))
    {
        initializer = expression();
    }

    consume(TokenType::SEMICOLON, "Expect ';' after variable declaration.");
    return std::make_unique<VarStmt>(name, std::move(initializer), modifier);
}

const Token &Parser::advance()
{
    if (!isAtEnd())
        current++;
    return previous();
}

bool Parser::check(const TokenType &type) const
{
    if (isAtEnd())
        return false;
    return peek().type() == type;
}

const Token &Parser::consume(const TokenType &type, const std::string &message)
{
    if (check(type))
        return advance();
    throw ParseError(message);
}

void Parser::error(const Token &token, const std::string &message)
{
    throw ParseError("[line " + std::to_string(token.line()) + "] Error at '" + token.lexeme() + "': " + message);
}

bool Parser::isAtEnd() const
{
    return peek().type() == TokenType::_EOF;
}

bool Parser::match(const std::initializer_list<TokenType> &types)
{
    for (auto type : types)
    {
        if (check(type))
        {
            advance();
            return true;
        }
    }

    return false;
}

const Token &Parser::peek() const
{
    return tokens[current];
}

const Token &Parser::previous() const
{
    return tokens[current - 1];
}

void Parser::synchronize()
{
    advance();

    while (!isAtEnd())
    {
        if (previous().type() == TokenType::SEMICOLON)
            return;

        switch (peek().type())
        {
        case TokenType::CLASS:
        case TokenType::FUN:
        case TokenType::LET:
        case TokenType::CONST:
        case TokenType::FOR:
        case TokenType::IF:
        case TokenType::WHILE:
        case TokenType::RETURN:
        case TokenType::PRINT:
            return;
        default:
            break;
        }

        advance();
    }
}