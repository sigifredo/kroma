

// catch2
#include <catch2/catch_test_macros.hpp>

// Own
#include <errors/FStringError.hpp>
#include <FStringScanner.hpp>
#include <Token.hpp>
#include <Value.hpp>

// std
#include <iostream>

TEST_CASE("FStringScanner: plain string")
{
    std::string str("Hola mundo");
    FStringScanner scanner(str);
    auto result = scanner.scanTokens();

    REQUIRE(result.size() == 1);
    REQUIRE(result[0].size() == 1);
    REQUIRE(result[0][0].type() == TokenType::STRING);
    REQUIRE(result[0][0].literal().isString());
    REQUIRE(result[0][0].literal().asString() == str);
}

TEST_CASE("FStringScanner: single expression")
{
    std::string str("Hola {nombre}");
    FStringScanner scanner(str);
    auto result = scanner.scanTokens();

    REQUIRE(result.size() == 2);

    // Literal
    REQUIRE(result[0][0].type() == TokenType::STRING);
    REQUIRE(result[0][0].literal().isString());
    REQUIRE(result[0][0].literal().asString() == "Hola ");

    // Expression
    REQUIRE(result[1].size() == 1);
    REQUIRE(result[1][0].type() == TokenType::IDENTIFIER);
    REQUIRE(result[1][0].lexeme() == "nombre");
}

TEST_CASE("FStringScanner: multiple expressions")
{
    FStringScanner scanner("Suma: {a + b}, doble: {2 * x}");
    auto result = scanner.scanTokens();

    REQUIRE(result.size() == 4);

    REQUIRE(result[0][0].type() == TokenType::STRING);
    REQUIRE(result[0][0].literal().isString());
    REQUIRE(result[0][0].literal().asString() == "Suma: ");

    REQUIRE(result[1].size() == 3); // a + b
    REQUIRE(result[1][0].type() == TokenType::IDENTIFIER);
    REQUIRE(result[1][1].type() == TokenType::PLUS);
    REQUIRE(result[1][2].type() == TokenType::IDENTIFIER);

    REQUIRE(result[2][0].type() == TokenType::STRING);
    REQUIRE(result[2][0].literal().isString());
    REQUIRE(result[2][0].literal().asString() == ", doble: ");

    REQUIRE(result[3].size() == 3); // 2 * x
    REQUIRE(result[3][0].type() == TokenType::NUMBER);
    REQUIRE(result[3][1].type() == TokenType::STAR);
    REQUIRE(result[3][2].type() == TokenType::IDENTIFIER);
}

TEST_CASE("FStringScanner: nested braces")
{
    FStringScanner scanner("expr: {fn({a})}");
    auto result = scanner.scanTokens();

    REQUIRE(result.size() == 2);
    REQUIRE(result[0][0].type() == TokenType::STRING);
    REQUIRE(result[0][0].literal().isString());
    REQUIRE(result[0][0].literal().asString() == "expr: ");

    // Debe contener fn ( ( { a } ) )
    REQUIRE(result[1].size() == 6);
    REQUIRE(result[1][0].type() == TokenType::IDENTIFIER);  // fn
    REQUIRE(result[1][1].type() == TokenType::LEFT_PAREN);  // (
    REQUIRE(result[1][2].type() == TokenType::LEFT_BRACE);  // {
    REQUIRE(result[1][3].type() == TokenType::IDENTIFIER);  // a
    REQUIRE(result[1][4].type() == TokenType::RIGHT_BRACE); // }
    REQUIRE(result[1][5].type() == TokenType::RIGHT_PAREN); // )
}

TEST_CASE("FStringScanner: unbalanced braces throws")
{
    FStringScanner scanner("Hola {nombre");

    REQUIRE_THROWS_AS(scanner.scanTokens(), FStringError);
}
