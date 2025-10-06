

// catch2
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

// own
#include <stmt/VarStmt.hpp>
#include <expressions/LiteralExpr.hpp>
#include <TestStmtVisitor.hpp>

// std
#include <memory>

TEST_CASE("VarStmt stores name, modifier, and initializer correctly", "[VarStmt]")
{
    Token nameToken(TokenType::IDENTIFIER, "x", 1);
    Token modifierToken(TokenType::CONST, "const", 1);

    auto initializer = std::make_unique<LiteralExpr>(Value(42));
    auto initializerRaw = initializer.get();

    VarStmt varStmt(nameToken, std::move(initializer), modifierToken);

    SECTION("Stores variable name correctly")
    {
        REQUIRE(varStmt.name().lexeme() == "x");
        REQUIRE(varStmt.name().type() == TokenType::IDENTIFIER);
    }

    SECTION("Stores modifier correctly")
    {
        REQUIRE(varStmt.modifier().type() == TokenType::CONST);
        REQUIRE(varStmt.modifier().lexeme() == "const");
    }

    SECTION("Stores initializer expression")
    {
        REQUIRE(varStmt.initializer() == initializerRaw);
    }
}
