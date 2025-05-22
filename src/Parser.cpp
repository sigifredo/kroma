

// Own
#include <Parser.hpp>
#include <BinaryExpr.hpp>
#include <GroupingExpr.hpp>
#include <LiteralExpr.hpp>
#include <UnaryExpr.hpp>

std::unique_ptr<Expr> Parser::parse()
{
    return expression();
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
    return equality();
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

std::unique_ptr<Expr> Parser::primary()
{
    if (match({TokenType::FALSE}))
        return std::make_unique<LiteralExpr>(false);
    if (match({TokenType::TRUE}))
        return std::make_unique<LiteralExpr>(true);
    if (match({TokenType::_NULL}))
        return std::make_unique<LiteralExpr>(nullptr);

    if (match({TokenType::NUMBER, TokenType::STRING}))
    {
        return std::make_unique<LiteralExpr>(previous().literal());
    }

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

    while (match({TokenType::MINUS, TokenType::PLUS}))
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

    return primary();
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