

// own
#include <Scanner.hpp>

// std
#include <iostream>

std::vector<Token> Scanner::scanTokens()
{
    while (!isAtEnd())
        scanToken();

    addToken(TokenType::_EOF, "", Value());
    return {tokens.begin(), tokens.end()};
}

void Scanner::addToken(const TokenType &type, const std::string &lexeme, const Value &value)
{
    tokens.emplace_back(type, lexeme, value, line());
}

void Scanner::scanIdentifier(const char &firstChar)
{
    std::string value(1, firstChar);

    while (!isAtEnd() && (std::isalnum(peek()) || peek() == '_'))
        value += advance();

    // Verificar si es palabra clave
    if (auto type = matchToken(value))
        addToken(type.value(), value, Value());
    else
        addToken(TokenType::IDENTIFIER, value, Value(value));
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

    addToken(TokenType::NUMBER, value, Value(std::stod(value)));
}

void Scanner::scanString(const char &delimiter, const bool &isFString)
{
    std::string value;

    while (!isAtEnd())
    {
        char c = advance();

        if (c == delimiter)
        {
            if (isFString)
                addToken(TokenType::FSTRING, value, Value(value));
            else
                addToken(TokenType::STRING, value, Value(value));
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
                newLine();
                break;
            default:
                std::cerr << "[Error] Unknown escape sequence: \\" << next << " at line " << line() << "\n";
                break;
            }
        }
        else if (c == '\n')
        {
            std::cerr << "[Error] Unterminated string (newline) at line " << line() << "\n";
            newLine();
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
            newLine();
        return;
    }

    if (c == '"' || c == '\'')
    {
        scanString(c, false);
        return;
    }

    if (std::isdigit(c))
    {
        scanNumber(c);
        return;
    }

    if (c == 'f' && (peek() == '\'' || peek() == '"'))
    {
        scanString(advance(), true);
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
        addToken(type.value(), twoChar, Value());
        return;
    }

    std::string oneChar(1, c);
    if (auto type = matchToken(oneChar))
    {
        addToken(type.value(), oneChar, Value());
        return;
    }

    std::cerr << "[Error] Unknown token: '" << c << "' at line " << line() << "\n";
}
