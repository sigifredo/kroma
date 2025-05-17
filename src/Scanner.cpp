

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

    for (size_t i = 0; i < source.length(); i++)
    {
        if (std::isspace(source[i]))
        {
            if (source[i] == '\n')
                line++;
        }
        else
        {
            std::string lexeme = source.substr(i, 2);
            std::optional<TokenType> type = matchToken(lexeme);

            if (type.has_value())
            {
                i++;
            }
            else
            {
                lexeme = source.substr(i, 1);
                type = matchToken(lexeme);
            }

            if (type.has_value())
            {
                tokens.push_back(Token(type.value(), lexeme, line));
            }
            else
            {
                std::cerr << "[Error] Unknown token: \"" << lexeme << "\"" << std::endl;
            }

            if (lexeme == "\n")
                ++line;
        }
    }

    tokens.push_back(Token(TokenType::_EOF, "", line));

    return tokens;
}