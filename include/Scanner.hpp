

#ifndef SCANNER_HPP
#define SCANNER_HPP

// own
#include <BaseScanner.hpp>

// std
#include <list>

class Scanner : public BaseScanner
{
public:
    explicit Scanner(const std::string &src) : BaseScanner(src) {}

    std::vector<Token> scanTokens() override;

private:
    std::list<Token> tokens;

    void addToken(const TokenType &type, const std::string &lexeme, const Value &value);

    void scanIdentifier(const char &firstChar);
    void scanNumber(const char &firstDigit);
    void scanString(const char &delimiter, const bool &isFString);
    void scanToken();
};

#endif