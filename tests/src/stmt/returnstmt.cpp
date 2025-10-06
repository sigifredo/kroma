

// catch2
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

// own
#include <expressions/LiteralExpr.hpp>
#include <stmt/ReturnStmt.hpp>
#include <TestStmtVisitor.hpp>

// std
#include <memory>

TEST_CASE("ReturnStmt stores and returns expression", "[ReturnStmt]")
{
    Token returnToken(TokenType::RETURN, "return");

    auto literal = std::make_unique<LiteralExpr>(42);
    auto rawPtr = literal.get();

    ReturnStmt stmt(returnToken, std::move(literal));

    REQUIRE(stmt.keyword().lexeme() == "return");
    REQUIRE(stmt.value() == rawPtr);
}

TEST_CASE("ReturnStmt accept calls visitReturnStmt", "[ReturnStmt]")
{
    Token returnToken(TokenType::RETURN, "return");
    ReturnStmt stmt(returnToken);
    TestStmtVisitor visitor;

    REQUIRE(stmt.accept(visitor) == "visited");
}
