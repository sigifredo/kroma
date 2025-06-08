

#ifndef INTERPRETERVISITOR_HPP
#define INTERPRETERVISITOR_HPP

class VarStmt;

class InterpreterVisitor
{
public:
    InterpreterVisitor() = default;
    virtual ~InterpreterVisitor() = default;

    virtual void visitVarStmt(const VarStmt &stmt) = 0;
};

#endif