

#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

// own
#include <Environment.hpp>
#include <InterpreterVisitor.hpp>

// std
#include <vector>

class Expr;
class Stmt;
class VarStmt;

class Interpreter : public InterpreterVisitor
{
public:
    Interpreter() = default;

    void interpret(const std::vector<std::unique_ptr<Stmt>> &statements);

    Value visitBinaryExpr(const BinaryExpr &expr) override;
    void visitVarStmt(const VarStmt &stmt) override;

    void printVariables() const;

private:
    Environment environment_;

    Value evaluate(const Expr &expr);
};

#endif
