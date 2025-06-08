

#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

// own
#include <Environment.hpp>
#include <InterpreterVisitor.hpp>

class Expr;
class VarStmt;

class Interpreter : public InterpreterVisitor
{
public:
    Interpreter() = default;

    Value visitBinaryExpr(const BinaryExpr &expr) override;
    void visitVarStmt(const VarStmt &stmt) override;

private:
    Environment environment_;

    Value evaluate(const Expr &expr);
};

#endif
