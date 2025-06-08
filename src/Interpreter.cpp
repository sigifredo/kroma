
// own
#include <Interpreter.hpp>
#include <expressions/Expr.hpp>
#include <stmt/VarStmt.hpp>

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