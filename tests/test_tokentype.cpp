

// catch2
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

// own
#include <TokenType.hpp>

TEST_CASE("matchToken returns correct TokenType for known lexemes", "[matchToken]")
{
    REQUIRE(matchToken("(") == TokenType::LEFT_PAREN);
    REQUIRE(matchToken(")") == TokenType::RIGHT_PAREN);
    REQUIRE(matchToken("{") == TokenType::LEFT_BRACE);
    REQUIRE(matchToken("}") == TokenType::RIGHT_BRACE);
    REQUIRE(matchToken(",") == TokenType::COMMA);
    REQUIRE(matchToken(".") == TokenType::DOT);
    REQUIRE(matchToken("..") == TokenType::DOT_DOT);
    REQUIRE(matchToken("-") == TokenType::MINUS);
    REQUIRE(matchToken("+") == TokenType::PLUS);
    REQUIRE(matchToken(";") == TokenType::SEMICOLON);
    REQUIRE(matchToken("/") == TokenType::SLASH);
    REQUIRE(matchToken("*") == TokenType::STAR);
    REQUIRE(matchToken("==") == TokenType::EQUAL_EQUAL);
    REQUIRE(matchToken("for") == TokenType::FOR);
    REQUIRE(matchToken("while") == TokenType::WHILE);
    REQUIRE(matchToken("fun") == TokenType::FUN);
    REQUIRE(matchToken("false") == TokenType::FALSE);
    REQUIRE(matchToken("by") == TokenType::BY);
}

TEST_CASE("matchToken returns nullopt for unknown lexemes", "[matchToken]")
{
    REQUIRE(matchToken("unknown") == std::nullopt);
    REQUIRE(matchToken("!@#") == std::nullopt);
    REQUIRE(matchToken("123") == std::nullopt);
    REQUIRE(matchToken("...") == std::nullopt);
    REQUIRE(matchToken("byy") == std::nullopt);
}

TEST_CASE("matchToken distinguishes between similar lexemes", "[matchToken]")
{
    REQUIRE(matchToken("==") == TokenType::EQUAL_EQUAL);
    REQUIRE(matchToken("=") == TokenType::EQUAL);
    REQUIRE(matchToken("!=") == TokenType::BANG_EQUAL);
    REQUIRE(matchToken("!") == TokenType::BANG);
    REQUIRE(matchToken(">=") == TokenType::GREATER_EQUAL);
    REQUIRE(matchToken(">") == TokenType::GREATER);
    REQUIRE(matchToken("<=") == TokenType::LESS_EQUAL);
    REQUIRE(matchToken("<") == TokenType::LESS);
}
