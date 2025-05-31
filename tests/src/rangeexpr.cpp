
// catch2
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

// own
#include <expressions/LiteralExpr.hpp>
#include <RangeExpr.hpp>
#include <TestVisitor.hpp>

// std
#include <memory>

TEST_CASE("RangeExpr stores start, end, step expressions", "[RangeExpr]")
{
    auto start = std::make_unique<LiteralExpr>(1);
    auto end = std::make_unique<LiteralExpr>(10);
    auto step = std::make_unique<LiteralExpr>(2);

    RangeExpr range(std::move(start), std::move(end), std::move(step));

    REQUIRE(dynamic_cast<const LiteralExpr *>(range.start())->value().asNumber() == 1);
    REQUIRE(dynamic_cast<const LiteralExpr *>(range.end())->value().asNumber() == 10);
    REQUIRE(dynamic_cast<const LiteralExpr *>(range.step())->value().asNumber() == 2);
}

TEST_CASE("RangeExpr accept method works with visitor", "[RangeExpr]")
{
    auto start = std::make_unique<LiteralExpr>(1);
    auto end = std::make_unique<LiteralExpr>(5);
    auto step = std::make_unique<LiteralExpr>(1);

    RangeExpr range(std::move(start), std::move(end), std::move(step));

    TestVisitor visitor;
    std::string result = range.accept(visitor);

    REQUIRE(result == "VisitedRange");
}