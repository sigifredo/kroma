

// own
#include <FStringScanner.hpp>
#include <Scanner.hpp>

// own errors
#include <errors/FStringError.hpp>

std::vector<std::vector<Token>> FStringScanner::scanTokens()
{
    std::vector<std::vector<Token>> result;
    std::string buffer;

    while (!isAtEnd())
    {
        char c = advance();

        if (c == '{')
        {
            if (!buffer.empty())
            {
                result.push_back({Token(TokenType::STRING, buffer, buffer, line())});
                buffer.clear();
            }

            std::string expr;
            int depth = 1;

            while (!isAtEnd() && depth > 0)
            {
                char inner = advance();

                if (inner == '{')
                    depth++;
                else if (inner == '}')
                    depth--;

                if (depth > 0)
                    expr += inner;
            }

            if (depth != 0)
                throw FStringError("Unbalanced braces in f-string.");

            Scanner exprScanner(expr);
            auto exprTokens = exprScanner.scanTokens();

            if (!exprTokens.empty() && exprTokens.back().type() == TokenType::_EOF)
                exprTokens.pop_back();

            result.push_back(std::move(exprTokens));
        }
        else
        {
            if (c == '\n')
                newLine();
            buffer += c;
        }
    }

    // Añade cualquier texto que quedó al final
    if (!buffer.empty())
    {
        result.push_back({Token(TokenType::STRING, buffer, buffer, line())});
    }

    return result;
}