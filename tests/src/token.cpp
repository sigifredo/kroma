

// catch2
#include <catch2/catch_test_macros.hpp>

// own
#include <Token.hpp>

TEST_CASE("Token constructor and getters", "[Token]")
{
    TokenType type = TokenType::IDENTIFIER;
    std::string lexeme = "variable";
    Value literal(42);
    int line = 10;

    Token token1(type, lexeme, literal, line);
    Token token2(TokenType::IDENTIFIER, "variable", 42, 10);

    REQUIRE(token1.type() == token2.type());
    REQUIRE(token1.lexeme() == token2.lexeme());
    REQUIRE(token1.literal() == token2.literal());
    REQUIRE(token1.line() == token2.line());

    REQUIRE(token1.type() == type);
    REQUIRE(token1.lexeme() == "variable");
    REQUIRE(token1.literal() == Value(42));
    REQUIRE(token1.literal() == 42);
    REQUIRE(token1.line() == 10);
}

TEST_CASE("Token toString produces correct format", "[Token]")
{
    TokenType type = TokenType::NUMBER;
    std::string lexeme = "123";
    Value literal(123.0);
    int line = 1;

    Token token(type, lexeme, literal, line);

    std::string expected = std::to_string(static_cast<int>(type)) + " (" + lexeme + ")";
    REQUIRE(token.toString() == expected);
}

TEST_CASE("Token supports copy construction and assignment", "[Token]")
{
    Token original(TokenType::STRING, "text", Value("hello"), 5);
    Token copy = original;

    REQUIRE(copy.type() == original.type());
    REQUIRE(copy.lexeme() == original.lexeme());
    REQUIRE(copy.literal() == original.literal());
    REQUIRE(copy.line() == original.line());

    Token assigned(TokenType::NUMBER, "0", Value(0), 0);
    assigned = original;

    REQUIRE(assigned.type() == original.type());
    REQUIRE(assigned.lexeme() == original.lexeme());
    REQUIRE(assigned.literal() == original.literal());
    REQUIRE(assigned.line() == original.line());
}
