

#ifndef INTERPRETERVISITOR_HPP
#define INTERPRETERVISITOR_HPP

// own
#include <Value.hpp>

// Expr
class AssignExpr;
class BinaryExpr;
class FStringExpr;
class LogicalExpr;
class UnaryExpr;
class VariableExpr;

// Stmt
class BlockStmt;
class ExpressionStmt;
class IfStmt;
class PrintStmt;
class VarStmt;

class InterpreterVisitor
{
public:
    InterpreterVisitor() = default;
    virtual ~InterpreterVisitor() = default;

    // --- Expr ---
    virtual Value visitAssignExpr(const AssignExpr &expr) = 0;
    virtual Value visitBinaryExpr(const BinaryExpr &expr) = 0;
    virtual Value visitFStringExpr(const FStringExpr &expr) = 0;
    virtual Value visitLogicalExpr(const LogicalExpr &expr) = 0;
    virtual Value visitUnaryExpr(const UnaryExpr &expr) = 0;
    virtual Value visitVariableExpr(const VariableExpr &expr) = 0;

    // --- Stmt ---
    virtual void visitBlockStmt(const BlockStmt &stmt) = 0;
    virtual void visitExpressionStmt(const ExpressionStmt &stmt) = 0;
    virtual void visitIfStmt(const IfStmt &stmt) = 0;
    virtual void visitPrintStmt(const PrintStmt &stmt) = 0;
    virtual void visitVarStmt(const VarStmt &stmt) = 0;
};

#endif