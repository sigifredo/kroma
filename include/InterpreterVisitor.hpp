

#ifndef INTERPRETERVISITOR_HPP
#define INTERPRETERVISITOR_HPP

// own
#include <Value.hpp>

class AssignExpr;
class BinaryExpr;
class ExpressionStmt;
class VarStmt;

class InterpreterVisitor
{
public:
    InterpreterVisitor() = default;
    virtual ~InterpreterVisitor() = default;

    // --- Expr ---
    virtual Value visitAssignExpr(const AssignExpr &expr) = 0;
    virtual Value visitBinaryExpr(const BinaryExpr &expr) = 0;

    // --- Stmt ---
    virtual void
    visitExpressionStmt(const ExpressionStmt &stmt) = 0;
    virtual void visitVarStmt(const VarStmt &stmt) = 0;
};

#endif