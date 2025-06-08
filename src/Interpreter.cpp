
// own
#include <Interpreter.hpp>
#include <expressions/BinaryExpr.hpp>
#include <expressions/Expr.hpp>
#include <stmt/VarStmt.hpp>
#include <Utils.hpp>

// std
#include <variant>

template <typename Op>
Value binaryNumericOp(const Value &left, const Value &right, Op op)
{
    const auto visitor = overloaded{
        [&](double a, double b)
        { return Value(op(a, b)); },
        [&](auto &&, auto &&) -> Value
        { throw std::runtime_error("Operands must be numbers."); }};

    return std::visit(visitor, left, right);
}

Value Interpreter::visitBinaryExpr(const BinaryExpr &expr)
{
    Value left = evaluate(*expr.left());
    Value right = evaluate(*expr.right());

    switch (expr.op().type())
    {
    case TokenType::PLUS:

        const auto visitor = overloaded{
            [](double a, double b)
            { return a + b; },
            [](const std::string &a, const std::string &b)
            { return a + b; },
            [](auto &&, auto &&) -> Value
            {
                throw std::runtime_error("Tipos incompatibles");
            }};

        return std::visit(visitor, left, right);

    case TokenType::MINUS:
        return binaryNumericOp(left, right, std::minus{});

    case TokenType::STAR:
        return binaryNumericOp(left, right, std::multiplies{});

    case TokenType::SLASH:
        return binaryNumericOp(left, right, [](double a, double b)
                               {
                if (b == 0) throw std::runtime_error("Division by zero.");
                return a / b; });
    default:
        throw std::runtime_error("Unknown binary operator.");
    }
}

void Interpreter::visitVarStmt(const VarStmt &stmt)
{
    Value value;

    if (stmt.initializer())
    {
        value = evaluate(*stmt.initializer());
    }
    else
    {
        value = Value{};
    }

    environment_.define(stmt.name().lexeme(), value);
}

Value Interpreter::evaluate(const Expr &expr)
{
    return expr.accept(*this);
}