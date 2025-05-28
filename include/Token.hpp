

#ifndef TOKEN_HPP
#define TOKEN_HPP

// own
#include <TokenType.hpp>
#include <Value.hpp>

// std
#include <string>

class Token
{
public:
    Token(const Token &other) = default;
    Token(const TokenType &type, const std::string &lexeme, const Value &literal, const int &line) : lexeme_(lexeme), line_(line), literal_(literal), type_(type) {}

    Token &operator=(const Token &other) = default;
    std::string toString();

    std::string lexeme() const;
    int line() const;
    const Value &literal() const;
    TokenType type() const;

private:
    std::string lexeme_;
    int line_;
    Value literal_;
    TokenType type_;
};

inline std::string Token::toString() { return std::to_string(static_cast<int>(type_)) + " (" + lexeme_ + ")"; }
inline std::string Token::lexeme() const { return lexeme_; }
inline int Token::line() const { return line_; }
inline const Value &Token::literal() const { return literal_; }
inline TokenType Token::type() const { return type_; }

#endif