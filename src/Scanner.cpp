

// Own
#include <Scanner.hpp>

Scanner::Scanner(const std::string &src)
{
    source = src;
}

std::list<Token> Scanner::scanToken()
{
    std::list<Token> tokens;
    int current = 0;
    int line = 1;
    int start = 0;

    for (const char &c : source)
    {
        start = current;

        char2token(c);
    }

    tokens.push_back(Token(TokenType::_EOF, std::string(), line));

    return tokens;
}