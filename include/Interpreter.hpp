

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
    Value visitLogicalExpr(const LogicalExpr &expr) override;
    Value visitUnaryExpr(const UnaryExpr &expr) override;
    Value visitVariableExpr(const VariableExpr &expr) override;

    // --- Stmt ---
    void visitBlockStmt(const BlockStmt &stmt) override;
    void visitExpressionStmt(const ExpressionStmt &stmt) override;
    void visitIfStmt(const IfStmt &stmt) override;
    void visitPrintStmt(const PrintStmt &stmt) override;
    void visitVarStmt(const VarStmt &stmt) override;

private:
    Environment environment_;

    Value evaluate(const Expr &expr);
    void execute(const Stmt &stmt);
    void executeBlock(const std::vector<std::unique_ptr<Stmt>> &statements, std::shared_ptr<Environment> newEnv);
    bool isTrue(const Value &value);
};

#endif
