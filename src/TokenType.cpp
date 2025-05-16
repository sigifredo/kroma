

// Own
#include <TokenType.hpp>

// std
#include <unordered_map>

namespace
{
    const std::unordered_map<char, TokenType> map = {
        {'(', TokenType::LEFT_PAREN},
        {')', TokenType::RIGHT_PAREN},
        {'{', TokenType::LEFT_BRACE},
        {'}', TokenType::RIGHT_BRACE},
        {',', TokenType::COMMA},
        {'.', TokenType::DOT},
        {'-', TokenType::MINUS},
        {'+', TokenType::PLUS},
        {';', TokenType::SEMICOLON},
        {'*', TokenType::SLASH},
        {'*', TokenType::STAR}};
}

TokenType char2token(const char &c)
{
    auto it = map.find(c);

    if (it != map.end())
    {
        return it->second;
    }
    else
    {
        return TokenType::UNKNOWN;
    }
}