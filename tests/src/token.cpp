
// catch2
#include <catch2/catch_test_macros.hpp>

// own
#include <Token.hpp>
#include <Value.hpp>

TEST_CASE("Token constructor and getters", "[Token]")
{
    TokenType type = TokenType::IDENTIFIER;
    std::string lexeme = "variable";
    Value literal(42);
    int line = 10;

    Token token(type, lexeme, literal, line);

    REQUIRE(token.type() == type);
    REQUIRE(token.lexeme() == "variable");
    REQUIRE(token.literal() == Value(42));
    REQUIRE(token.literal() == 42);
    REQUIRE(token.line() == 10);
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
