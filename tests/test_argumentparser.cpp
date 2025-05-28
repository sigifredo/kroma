
// catch2
#include <catch2/catch_test_macros.hpp>

// own
#include <ArgumentParser.hpp>

TEST_CASE("ArgumentParser can add and parse positional arguments", "[ArgumentParser]")
{
    ArgumentParser parser("test_program");
    parser.addArgument({"filename"}, "Input file", true);

    const char *argv[] = {"test_program", "input.txt"};
    parser.parse(2, const_cast<char **>(argv));

    REQUIRE(parser.isSet("filename"));
    REQUIRE(parser.get("filename") == "input.txt");
}

TEST_CASE("ArgumentParser can parse flags", "[ArgumentParser]")
{
    ArgumentParser parser("test_program");
    parser.addArgument({"-v", "--verbose"}, "Enable verbose mode", false, "", true);

    const char *argv[] = {"test_program", "-v"};
    parser.parse(2, const_cast<char **>(argv));

    REQUIRE(parser.isSet("-v"));
    REQUIRE(parser.isSet("--verbose"));
    REQUIRE(parser.get("-v") == "true");
}

TEST_CASE("ArgumentParser handles default values", "[ArgumentParser]")
{
    ArgumentParser parser("test_program");
    parser.addArgument({"output"}, "Output file", false, "default.txt");

    const char *argv[] = {"test_program"};
    parser.parse(1, const_cast<char **>(argv));

    REQUIRE(parser.isSet("output") == false);
    REQUIRE(parser.get("output") == "default.txt");
}

TEST_CASE("ArgumentParser throws on missing required argument", "[ArgumentParser]")
{
    ArgumentParser parser("test_program");
    parser.addArgument({"filename"}, "Input file", true);

    const char *argv[] = {"test_program"};
    REQUIRE_THROWS_AS(parser.parse(1, const_cast<char **>(argv)), std::runtime_error);
}

TEST_CASE("ArgumentParser throws on unknown argument", "[ArgumentParser]")
{
    ArgumentParser parser("test_program");

    const char *argv[] = {"test_program", "--unknown"};
    REQUIRE_THROWS_AS(parser.parse(2, const_cast<char **>(argv)), std::runtime_error);
}

TEST_CASE("ArgumentParser parses multiple arguments and flags", "[ArgumentParser]")
{
    ArgumentParser parser("test_program");
    parser.addArgument({"input"}, "Input file", true);
    parser.addArgument({"output"}, "Output file", false, "out.txt");
    parser.addArgument({"-v", "--verbose"}, "Verbose flag", false, "", true);

    const char *argv[] = {"test_program", "in.txt", "-v"};
    parser.parse(3, const_cast<char **>(argv));

    REQUIRE(parser.isSet("input"));
    REQUIRE(parser.get("input") == "in.txt");

    REQUIRE(parser.isSet("output") == false);
    REQUIRE(parser.get("output") == "out.txt");

    REQUIRE(parser.isSet("-v"));
    REQUIRE(parser.get("-v") == "true");
}
