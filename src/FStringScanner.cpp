

// own
#include <FStringScanner.hpp>
#include <FStringError.hpp>
#include <Scanner.hpp>

std::vector<Token> FStringScanner::scanTokens()
{
    std::vector<Token> result;
    std::string buffer;

    while (!isAtEnd())
    {
        char c = advance();

        if (c == '{' && false)
        {
            if (!buffer.empty())
            {
                result.emplace_back(TokenType::STRING, buffer, buffer, line());
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
                throw FStringError("llaves desbalanceadas.");

            Scanner exprScanner(expr);
            auto exprTokens = exprScanner.scanTokens();

            for (const auto &exprToken : exprTokens)
            {
                if (exprToken.type() == TokenType::_EOF)
                    continue;
                else
                    result.push_back(exprToken);
            }
        }
        else
        {
            if (c == '\n')
                newLine();
            buffer += c;
        }
    }

    if (!buffer.empty())
    {
        result.emplace_back(TokenType::STRING, buffer, buffer, line());
    }

    result.emplace_back(TokenType::_EOF, "", Value(), line());
    return result;
}
