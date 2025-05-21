

// Own
#include <Scanner.hpp>

// std
#include <iostream>

Scanner::Scanner(const std::string &src)
{
    source = src;
    current = 0;
    line = 1;
}

std::list<Token> Scanner::scanTokens()
{
    while (!isAtEnd())
        scanToken(); // Analiza un solo token

    addToken(TokenType::_EOF, "");
    return tokens;
}

char Scanner::advance()
{
    return source[current++];
}

void Scanner::addToken(const TokenType &type, const std::string &lexeme)
{
    tokens.emplace_back(type, lexeme, line);
}

bool Scanner::match(const char &expected)
{
    if (isAtEnd() || source[current] != expected)
        return false;

    ++current;
    return true;
}

char Scanner::peek() const
{
    return isAtEnd() ? '\0' : source[current];
}

char Scanner::peekNext() const
{
    return (current + 1 >= source.length()) ? '\0' : source[current + 1];
}

bool Scanner::isAtEnd() const
{
    return current >= source.length();
}

void Scanner::scanIdentifier(const char &firstChar)
{
    std::string value(1, firstChar);

    while (!isAtEnd() && (std::isalnum(peek()) || peek() == '_'))
        value += advance();

    // Verificar si es palabra clave
    if (auto type = matchToken(value))
        addToken(type.value(), value);
    else
        addToken(TokenType::IDENTIFIER, value);
}

void Scanner::scanNumber(const char &firstDigit)
{
    std::string value(1, firstDigit);

    auto consumeWhile = [&](auto condition)
    {
        while (!isAtEnd() && condition(peek()))
            value += advance();
    };

    consumeWhile([](char c)
                 { return std::isdigit(c); });

    // Comprobamos si hay parte decimal
    if (!isAtEnd() && peek() == '.' && std::isdigit(peekNext()))
    {
        value += advance(); // consumir '.'

        consumeWhile([](char c)
                     { return std::isdigit(c); });
    }

    addToken(TokenType::NUMBER, value);
}

void Scanner::scanString(const char &delimiter)
{
    std::string value;

    while (!isAtEnd())
    {
        char c = advance();

        if (c == delimiter)
        {
            addToken(TokenType::STRING, value);
            return;
        }

        if (c == '\\')
        {
            if (isAtEnd())
            {
                std::cerr << "[Error] Incomplete escape sequence at end of input\n";
                return;
            }

            char next = advance();
            switch (next)
            {
            case 'n':
                value += '\n';
                break;
            case 't':
                value += '\t';
                break;
            case '"':
                value += '"';
                break;
            case '\'':
                value += '\'';
                break;
            case '\\':
                value += '\\';
                break;
            case '\n':
                ++line;
                break;
            default:
                std::cerr << "[Error] Unknown escape sequence: \\" << next << " at line " << line << "\n";
                break;
            }
        }
        else if (c == '\n')
        {
            std::cerr << "[Error] Unterminated string (newline) at line " << line << "\n";
            ++line;
            return;
        }
        else
        {
            value += c;
        }
    }

    std::cerr << "[Error] Unterminated string at end of file\n";
}

void Scanner::scanToken()
{
    char c = advance();

    if (std::isspace(c))
    {
        if (c == '\n')
            ++line;
        return;
    }

    if (c == '"' || c == '\'')
    {
        scanString(c);
        return;
    }

    if (std::isdigit(c))
    {
        scanNumber(c);
        return;
    }

    if (std::isalpha(c) || c == '_')
    {
        scanIdentifier(c);
        return;
    }

    std::string twoChar = std::string(1, c) + peek();
    if (auto type = matchToken(twoChar))
    {
        advance(); // consumir segundo carácter
        addToken(type.value(), twoChar);
        return;
    }

    std::string oneChar(1, c);
    if (auto type = matchToken(oneChar))
    {
        addToken(type.value(), oneChar);
        return;
    }

    std::cerr << "[Error] Unknown token: '" << c << "' at line " << line << "\n";
}
