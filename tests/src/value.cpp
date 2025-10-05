
// catch2
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

// own
#include <Value.hpp>

TEST_CASE("Value supports empty construction", "[Value]")
{
    Value v;
    REQUIRE(v.isNull());
}

TEST_CASE("Value supports construction from int", "[Value]")
{
    Value v(41);
    REQUIRE(v.isNumber());
    REQUIRE(v.asNumber() == Catch::Approx(41.0));
}

TEST_CASE("Value supports construction from int64_t", "[Value]")
{
    std::int64_t number = 35;
    Value v(number);

    REQUIRE(v.isNumber());
    REQUIRE(v.asNumber() == Catch::Approx(35.0));
}

TEST_CASE("Value supports construction from double", "[Value]")
{
    Value v(3.1415);

    REQUIRE(v.isNumber());
    REQUIRE(v.asNumber() == Catch::Approx(3.1415));
}

TEST_CASE("Value supports construction from std::string", "[Value]")
{
    Value v(std::string("hello"));

    REQUIRE(v.isString());
    REQUIRE(v.asString() == "hello");
}

TEST_CASE("Value supports construction from const char*", "[Value]")
{
    Value v("world");

    REQUIRE(v.isString());
    REQUIRE(v.asString() == "world");
}

TEST_CASE("Value supports construction from bool", "[Value]")
{
    Value v(true);

    REQUIRE(v.isBool());
    REQUIRE(v.asBool());
}

TEST_CASE("Value supports equality operator", "[Value]")
{
    Value v1(42);
    Value v2(42.0);
    REQUIRE(v1 == v2);
    REQUIRE(v1 == 42);

    Value s1("hello");
    Value s2(std::string("hello"));
    REQUIRE(s1.asString() == "hello");
    REQUIRE(s1 == s2);

    Value b1(true);
    Value b2(true);
    REQUIRE(b1.asBool() == true);
    REQUIRE(b1 == b2);

    Value a1({1, 2, 3});
    Value a2({1, 2, 3});
    REQUIRE(a1 == a2);
}

TEST_CASE("Value supports inequality operator", "[Value]")
{
    Value v1(42);
    Value v2(42.1);
    REQUIRE(v1 != v2);
    REQUIRE(v1 != 41);

    Value s1("hello");
    Value s2(std::string("hello "));
    REQUIRE(s1.asString() != "hello!");
    REQUIRE(s1 != s2);

    Value b1(true);
    Value b2(false);
    REQUIRE(b1.asBool() != false);
    REQUIRE(b1 != b2);

    Value a1({1, 2, 3});
    Value a2({1, 3});
    REQUIRE(a1 != a2);
}

TEST_CASE("Value supports toString()", "[Value]")
{
    Value v1(42);
    REQUIRE(v1.toString() == "42");

    Value v2(3.14);
    REQUIRE(v2.toString() == "3.14");

    Value v3("test");
    REQUIRE(v3.toString() == "test");

    Value v4(true);
    REQUIRE(v4.toString() == "true");

    Value v5(false);
    REQUIRE(v5.toString() == "false");

    Value v6;
    REQUIRE(v6.toString() == "null");

    Value v7({1, 2});
    REQUIRE(v7.toString() == "[1, 2]");
}
