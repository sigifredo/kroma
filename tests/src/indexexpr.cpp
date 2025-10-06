

// catch2
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

// own
#include <expressions/IndexExpr.hpp>
#include <expressions/LiteralExpr.hpp>
#include <expressions/ListExpr.hpp>
#include <Interpreter.hpp>
#include <TestExprVisitor.hpp>

// std
#include <memory>

TEST_CASE("IndexExpr index access", "[IndexExpr]")
{
    std::vector<std::unique_ptr<Expr>> elements;
    elements.push_back(std::make_unique<LiteralExpr>(1.0));
    elements.push_back(std::make_unique<LiteralExpr>(2.0));
    elements.push_back(std::make_unique<LiteralExpr>(3.0));

    auto target = std::make_unique<ListExpr>(std::move(elements));
    auto index = std::make_unique<LiteralExpr>(1.0);
    Token lbrack(TokenType::LEFT_BRACKET, "[", Value(), 1);
    auto expr = std::make_unique<IndexExpr>(std::move(target),
                                            std::move(index),
                                            lbrack);

    Interpreter interpreter;
    Value result = expr->accept(interpreter);
    REQUIRE(result.asNumber() == Catch::Approx(2.0));
}
