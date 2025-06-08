
// catch2
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

// own
#include <expressions/LiteralExpr.hpp>
#include <stmt/ExpressionStmt.hpp>
#include <TestStmtVisitor.hpp>

// std
#include <memory>

TEST_CASE("ExpressionStmt stores and returns expression", "[ExpressionStmt]")
{
    auto literal = std::make_unique<LiteralExpr>(42);
    auto rawPtr = literal.get();
    ExpressionStmt stmt(std::move(literal));

    REQUIRE(stmt.expression() == rawPtr);
}

TEST_CASE("ExpressionStmt accept calls visitor", "[ExpressionStmt]")
{
    auto literal = std::make_unique<LiteralExpr>(42);
    ExpressionStmt stmt(std::move(literal));
    TestStmtVisitor visitor;

    REQUIRE(stmt.accept(visitor) == "visited");
}