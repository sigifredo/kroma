

#ifndef PARSER_HPP
#define PARSER_HPP

// own
#include <expressions/Expr.hpp>
#include <Token.hpp>

// std
#include <memory>
#include <optional>
#include <stdexcept>
#include <vector>

class Parser
{
public:
    explicit Parser(const std::vector<Token> &tokens);

    std::unique_ptr<Expr> parse();

private:
    const std::vector<Token> &tokens;
    size_t current = 0;

    std::unique_ptr<Expr> assignment();
    std::unique_ptr<Expr> call();
    std::unique_ptr<Expr> comparison();
    std::unique_ptr<Expr> equality();
    std::unique_ptr<Expr> expression();
    std::unique_ptr<Expr> factor();
    std::unique_ptr<Expr> finishCall(std::unique_ptr<Expr> callee);
    std::unique_ptr<Expr> logicAnd();
    std::unique_ptr<Expr> logicOr();
    std::unique_ptr<Expr> primary();
    std::unique_ptr<Expr> range();
    std::unique_ptr<Expr> term();
    std::unique_ptr<Expr> unary();

    const Token &advance();
    bool check(const TokenType &type) const;
    const Token &consume(const TokenType &type, const std::string &message);
    void error(const Token &token, const std::string &message);
    bool isAtEnd() const;
    bool match(const std::initializer_list<TokenType> &types);
    const Token &peek() const;
    const Token &previous() const;
};

#endif