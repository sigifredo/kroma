

// catch2
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

// own
#include <expressions/LiteralExpr.hpp>
#include <expressions/RangeExpr.hpp>
#include <Interpreter.hpp>
#include <TestExprVisitor.hpp>

// std
#include <memory>
#include <string>

template <class T>
static void expect_vec_eq(const std::vector<T> &got,
                          const std::vector<T> &exp,
                          const char *scenario)
{
    CAPTURE(scenario);
    REQUIRE(got.size() == exp.size());

    for (size_t i = 0; i < exp.size(); ++i)
    {
        CAPTURE(i);
        REQUIRE(got[i] == exp[i]);
    }
}

TEST_CASE("RangeExpr stores start, end expressions", "[RangeExpr]")
{
    auto start = std::make_unique<LiteralExpr>(1);
    auto end = std::make_unique<LiteralExpr>(10);

    RangeExpr range(std::move(start),
                    std::move(end));

    REQUIRE(dynamic_cast<const LiteralExpr *>(range.start())->value().asNumber() == 1);
    REQUIRE(dynamic_cast<const LiteralExpr *>(range.end())->value().asNumber() == 10);
    REQUIRE(dynamic_cast<const LiteralExpr *>(range.step()) == nullptr);
}

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

    RangeExpr range(std::move(start),
                    std::move(end),
                    std::move(step));

    TestExprVisitor visitor;
    std::string result = range.accept(visitor);

    REQUIRE(result == "Visited");
}

TEST_CASE("RangeExpr exposes non-null start/end and null step when omitted", "[RangeExpr]")
{
    RangeExpr range(std::make_unique<LiteralExpr>(-3),
                    std::make_unique<LiteralExpr>(4));

    REQUIRE(range.start() != nullptr);
    REQUIRE(range.end() != nullptr);
    REQUIRE(range.step() == nullptr);

    REQUIRE(dynamic_cast<const LiteralExpr *>(range.start())->value().asNumber() == -3);
    REQUIRE(dynamic_cast<const LiteralExpr *>(range.end())->value().asNumber() == 4);
}

TEST_CASE("RangeExpr stores negative step expression", "[RangeExpr]")
{
    RangeExpr range(std::make_unique<LiteralExpr>(7),
                    std::make_unique<LiteralExpr>(1),
                    std::make_unique<LiteralExpr>(-2));

    REQUIRE(dynamic_cast<const LiteralExpr *>(range.start())->value().asNumber() == 7);
    REQUIRE(dynamic_cast<const LiteralExpr *>(range.end())->value().asNumber() == 1);
    REQUIRE(dynamic_cast<const LiteralExpr *>(range.step())->value().asNumber() == -2);
}

TEST_CASE("RangeExpr single-element range stores equal start/end", "[RangeExpr]")
{
    RangeExpr range(std::make_unique<LiteralExpr>(5),
                    std::make_unique<LiteralExpr>(5));

    REQUIRE(dynamic_cast<const LiteralExpr *>(range.start())->value().asNumber() == 5);
    REQUIRE(dynamic_cast<const LiteralExpr *>(range.end())->value().asNumber() == 5);
    REQUIRE(range.step() == nullptr);
}

TEST_CASE("RangeExpr accept keeps children intact", "[RangeExpr]")
{
    auto start = std::make_unique<LiteralExpr>(1);
    auto end = std::make_unique<LiteralExpr>(7);
    auto step = std::make_unique<LiteralExpr>(2);

    const double a = start->value().asNumber();
    const double b = end->value().asNumber();
    const double c = step->value().asNumber();

    RangeExpr range(std::move(start),
                    std::move(end),
                    std::move(step));

    TestExprVisitor v;
    REQUIRE(range.accept(v) == "Visited");

    REQUIRE(dynamic_cast<const LiteralExpr *>(range.start())->value().asNumber() == a);
    REQUIRE(dynamic_cast<const LiteralExpr *>(range.end())->value().asNumber() == b);
    REQUIRE(dynamic_cast<const LiteralExpr *>(range.step())->value().asNumber() == c);
}

TEST_CASE("RangeExpr supports large exact integers representable in double", "[RangeExpr]")
{
    constexpr int64_t big_exact = static_cast<int64_t>(9007199254740991LL); // 2^53 - 1

    RangeExpr range(std::make_unique<LiteralExpr>(big_exact),
                    std::make_unique<LiteralExpr>(big_exact));

    auto a = static_cast<int64_t>(dynamic_cast<const LiteralExpr *>(range.start())->value().asNumber());
    auto b = static_cast<int64_t>(dynamic_cast<const LiteralExpr *>(range.end())->value().asNumber());

    REQUIRE(a == big_exact);
    REQUIRE(b == big_exact);
    REQUIRE(range.step() == nullptr);
}

TEST_CASE("RangeExpr stores zero step (semantic error deferred to evaluator)", "[RangeExpr]")
{
    RangeExpr range(std::make_unique<LiteralExpr>(1),
                    std::make_unique<LiteralExpr>(4),
                    std::make_unique<LiteralExpr>(0));

    REQUIRE(dynamic_cast<const LiteralExpr *>(range.step())->value().asNumber() == 0);
}

TEST_CASE("RangeExpr eval basic cases", "[RangeExpr][eval]")
{
    Interpreter it;

    SECTION("1..4")
    {
        RangeExpr e(std::make_unique<LiteralExpr>(int64_t{1}),
                    std::make_unique<LiteralExpr>(int64_t{4}));
        auto v = it.visitRangeExpr(e).asList();
        expect_vec_eq(v, decltype(v){1, 2, 3, 4}, "1..4");
    }

    SECTION("1..7 by 2")
    {
        RangeExpr e(std::make_unique<LiteralExpr>(1),
                    std::make_unique<LiteralExpr>(7),
                    std::make_unique<LiteralExpr>(2));
        auto v = it.visitRangeExpr(e).asList();
        expect_vec_eq(v, decltype(v){1, 3, 5, 7}, "1..7 by 2");
    }

    SECTION("7..1 by -2")
    {
        RangeExpr e(std::make_unique<LiteralExpr>(7),
                    std::make_unique<LiteralExpr>(1),
                    std::make_unique<LiteralExpr>(-2));
        auto v = it.visitRangeExpr(e).asList();
        expect_vec_eq(v, decltype(v){7, 5, 3, 1}, "7..1 by -2");
    }

    SECTION("1..4 by 0.5")
    {
        RangeExpr e(std::make_unique<LiteralExpr>(1),
                    std::make_unique<LiteralExpr>(4),
                    std::make_unique<LiteralExpr>(0.5));

        auto v = it.visitRangeExpr(e).asList();
        expect_vec_eq(v, decltype(v){1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0}, "1..4 by 0.5");
    }

    SECTION("7..1 by -2")
    {
        RangeExpr e(std::make_unique<LiteralExpr>(7),
                    std::make_unique<LiteralExpr>(1),
                    std::make_unique<LiteralExpr>(-1.5));
        auto v = it.visitRangeExpr(e).asList();
        expect_vec_eq(v, decltype(v){7.0, 5.5, 4.0, 2.5, 1.0}, "7..1 by -1.5");
    }
}