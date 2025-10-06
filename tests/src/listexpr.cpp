

// catch2
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

// own
#include <expressions/LiteralExpr.hpp>
#include <expressions/ListExpr.hpp>
#include <Interpreter.hpp>
#include <TestExprVisitor.hpp>

// std
#include <memory>

TEST_CASE("ListExpr evaluation returns correct list", "[ListExpr]")
{
    std::vector<std::unique_ptr<Expr>> elements;
    elements.push_back(std::make_unique<LiteralExpr>(1.0));
    elements.push_back(std::make_unique<LiteralExpr>(2.0));
    elements.push_back(std::make_unique<LiteralExpr>(3.0));

    ListExpr listExpr(std::move(elements));

    Interpreter interpreter;
    Value result = interpreter.visitListExpr(listExpr);

    REQUIRE(result.isList());
    const auto &vec = result.asList();
    INFO("Tamaño actual: " << result);
    REQUIRE(vec.size() == 3);
    REQUIRE(vec[0] == Value(1.0));
    REQUIRE(vec[1] == Value(2.0));
    REQUIRE(vec[2] == Value(3.0));
}
