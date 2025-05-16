

// Own
#include <Scanner.hpp>

// std
#include <iostream>

Scanner::Scanner(const std::string &src)
{
    source = src;
}

std::list<Token> Scanner::scanTokens()
{
    int line = 1;

    for (size_t i = 0; i < source.length(); ++i)
    {
        char c = source[i];

        TokenType type = char2token(c);

        if (type == TokenType::UNKNOWN)
        {
            std::cerr << "[Error] Unknown token: \"" << c << "\"" << std::endl;
        }
        else
        {
            tokens.push_back(Token(type, std::string(1, c), line));
        }

        if (c == '\n')
            ++line;
    }

    tokens.push_back(Token(TokenType::_EOF, "", line));

    return tokens;
}