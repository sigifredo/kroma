

// Own
#include <TokenType.hpp>

// std
#include <unordered_map>

namespace
{
    const std::unordered_map<std::string, TokenType> token_map = {
        {"(", TokenType::LEFT_PAREN},
        {")", TokenType::RIGHT_PAREN},
        {"{", TokenType::LEFT_BRACE},
        {"}", TokenType::RIGHT_BRACE},
        {",", TokenType::COMMA},
        {".", TokenType::DOT},
        {"-", TokenType::MINUS},
        {"+", TokenType::PLUS},
        {";", TokenType::SEMICOLON},
        {"/", TokenType::SLASH},
        {"*", TokenType::STAR},

        // One or two character token
        {"!", TokenType::BANG},
        {"!=", TokenType::BANG_EQUAL},
        {"=", TokenType::EQUAL},
        {"==", TokenType::EQUAL_EQUAL},
        {">", TokenType::GREATER},
        {">=", TokenType::GREATER_EQUAL},
        {"<", TokenType::LESS},
        {"<=", TokenType::LESS_EQUAL}};
}

std::optional<TokenType> matchToken(const std::string &lexeme)
{
    auto it = token_map.find(lexeme);

    if (it != token_map.end())
    {
        return it->second;
    }

    return std::nullopt;
}