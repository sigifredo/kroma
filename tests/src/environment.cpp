
// catch2
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

// own
#include <Environment.hpp>
#include <RuntimeError.hpp>

TEST_CASE("Environment can define and retrieve variables", "[Environment]")
{
    auto env = std::make_shared<Environment>();

    env->define("x", Value(42));
    Value v = env->get("x");
    REQUIRE(v.isNumber());
    REQUIRE(v.asNumber() == Catch::Approx(42.0));
}

TEST_CASE("Environment throws when getting undefined variable", "[Environment]")
{
    auto env = std::make_shared<Environment>();
    REQUIRE_THROWS_AS(env->get("undefined"), RuntimeError);
}

TEST_CASE("Environment can assign existing variable", "[Environment]")
{
    auto env = std::make_shared<Environment>();

    env->define("x", Value(10));
    env->assign("x", Value(20));

    Value v = env->get("x");
    REQUIRE(v.asNumber() == Catch::Approx(20.0));
}

TEST_CASE("Environment throws when assigning undefined variable", "[Environment]")
{
    auto env = std::make_shared<Environment>();

    REQUIRE_THROWS_AS(env->assign("x", Value(1)), RuntimeError);
}

TEST_CASE("Environment supports enclosing scopes", "[Environment]")
{
    auto outer = std::make_shared<Environment>();
    outer->define("a", Value(100));

    auto inner = std::make_shared<Environment>(outer);

    Value v = inner->get("a");
    REQUIRE(v.asNumber() == Catch::Approx(100));

    inner->define("b", Value(200));
    REQUIRE_THROWS_AS(outer->get("b"), RuntimeError);
}
