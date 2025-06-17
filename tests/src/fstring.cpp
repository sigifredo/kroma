#include <catch2/catch_test_macros.hpp>
#include <Parser.hpp>
#include <Scanner.hpp>
#include <expressions/BinaryExpr.hpp>
#include <expressions/LiteralExpr.hpp>
#include <expressions/VariableExpr.hpp>

TEST_CASE("Parser: fstring simple", "[parser][fstring]")
{
    std::string source = R"(f"Hola {nombre}, edad: {2 + 1}")";

    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanTokens();

    Parser parser(tokens);
    auto expr = parser.expression(); // asumimos que llama a fstring()

    // Verificamos que sea BinaryExpr de BinaryExpr de Literal y Variable
    auto outer = dynamic_cast<BinaryExpr *>(expr.get());
    REQUIRE(outer != nullptr);

    auto left = dynamic_cast<BinaryExpr *>(outer->left().get());
    REQUIRE(left != nullptr);

    auto left_literal = dynamic_cast<LiteralExpr *>(left->left().get());
    REQUIRE(left_literal != nullptr);
    REQUIRE(left_literal->value() == "Hola ");

    auto var_expr = dynamic_cast<VariableExpr *>(left->right().get());
    REQUIRE(var_expr != nullptr);
    REQUIRE(var_expr->name().lexeme == "nombre");

    auto right = dynamic_cast<BinaryExpr *>(outer->right().get());
    REQUIRE(right != nullptr);

    auto right_literal = dynamic_cast<LiteralExpr *>(right->left().get());
    REQUIRE(right_literal != nullptr);
    REQUIRE(right_literal->value() == ", edad: ");

    auto sum = dynamic_cast<BinaryExpr *>(right->right().get());
    REQUIRE(sum != nullptr);

    auto num2 = dynamic_cast<LiteralExpr *>(sum->left().get());
    auto num1 = dynamic_cast<LiteralExpr *>(sum->right().get());

    REQUIRE(num2 != nullptr);
    REQUIRE(num1 != nullptr);
    REQUIRE(num2->value() == "2");
    REQUIRE(num1->value() == "1");
}
