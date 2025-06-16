

#ifndef SCANNER_HPP
#define SCANNER_HPP

// own
#include <BaseScanner.hpp>
#include <Token.hpp>

// std
#include <list>
#include <vector>

class Scanner : public BaseScanner
{
public:
    explicit Scanner(const std::string &src);
    std::vector<Token> scanTokens();

private:
    std::list<Token> tokens;

    void addToken(const TokenType &type, const std::string &lexeme, const Value &value);

    void scanIdentifier(const char &firstChar);
    void scanNumber(const char &firstDigit);
    void scanString(const char &delimiter);
    void scanToken();
};

#endif