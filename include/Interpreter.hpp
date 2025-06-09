

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
    void printVariables() const;

    // --- Expr ---
    Value visitAssignExpr(const AssignExpr &expr) override;
    Value visitBinaryExpr(const BinaryExpr &expr) override;

    // --- Stmt ---
    void visitExpressionStmt(const ExpressionStmt &stmt) override;
    void visitVarStmt(const VarStmt &stmt) override;

private:
    Environment environment_;

    Value evaluate(const Expr &expr);
};

#endif
