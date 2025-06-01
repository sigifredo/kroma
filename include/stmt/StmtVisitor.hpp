

#ifndef STMT_STMTVISITOR_HPP
#define STMT_STMTVISITOR_HPP

class BlockStmt;
class ClassStmt;
class ExpressionStmt;
class ForEachStmt;
class ForRangeStmt;
class FunctionStmt;
class IfStmt;
class VarStmt;

class StmtVisitor
{
public:
    StmtVisitor() = default;
    virtual ~StmtVisitor() = default;

    virtual void visitBlockStmt(const BlockStmt &stmt) = 0;
    virtual void visitClassStmt(const ClassStmt &stmt) = 0;
    virtual void visitExpressionStmt(const ExpressionStmt &stmt) = 0;
    virtual void visitForEachStmt(const ForEachStmt &stmt) = 0;
    virtual void visitForRangeStmt(const ForRangeStmt &stmt) = 0;
    virtual void visitFunctionStmt(const FunctionStmt &stmt) = 0;
    virtual void visitIfStmt(const IfStmt &stmt) = 0;
    virtual void visitVarStmt(const VarStmt &stmt) = 0;
};

#endif