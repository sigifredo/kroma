

// Own
#include <Parser.hpp>
#include <expressions/AssignExpr.hpp>
#include <expressions/BinaryExpr.hpp>
#include <expressions/CallExpr.hpp>
#include <expressions/GetExpr.hpp>
#include <expressions/GroupingExpr.hpp>
#include <expressions/LiteralExpr.hpp>
#include <expressions/LogicalExpr.hpp>
#include <expressions/UnaryExpr.hpp>
#include <expressions/VariableExpr.hpp>
#include <sstream>

Parser::Parser(const std::vector<Token> &tokens) : tokens(tokens) {}

std::unique_ptr<Expr> Parser::parse()
{
    return expression();
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
    auto expr = term();

    while (match({TokenType::GREATER, TokenType::GREATER_EQUAL,
                  TokenType::LESS, TokenType::LESS_EQUAL}))
    {
        Token op = previous();
        auto right = term();
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

    throw std::runtime_error("Expected expression.");
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

const Token &Parser::advance()
{
    if (!isAtEnd())
        current++;
    return previous();
}

bool Parser::check(TokenType type) const
{
    if (isAtEnd())
        return false;
    return peek().type() == type;
}

const Token &Parser::consume(TokenType type, const std::string &message)
{
    if (check(type))
        return advance();
    throw std::runtime_error(message);
}

void Parser::error(const Token &token, const std::string &message)
{
    std::ostringstream oss;
    oss << "[line " << token.line() << "] Error at '" << token.lexeme() << "': " << message;
    throw std::runtime_error(oss.str());
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
