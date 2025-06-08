

#ifndef INTERPRETERVISITOR_HPP
#define INTERPRETERVISITOR_HPP

// own
#include <Value.hpp>

class BinaryExpr;
class VarStmt;

class InterpreterVisitor
{
public:
    InterpreterVisitor() = default;
    virtual ~InterpreterVisitor() = default;

    // --- Expr ---
    virtual Value visitBinaryExpr(const BinaryExpr &expr) = 0;

    // --- Stmt ---
    virtual void visitVarStmt(const VarStmt &stmt) = 0;
};

#endif