

#ifndef TEST_TESTSTMTVISITOR_HPP
#define TEST_TESTSTMTVISITOR_HPP

#include <stmt/StmtVisitor.hpp>

class TestStmtVisitor : public StmtVisitor
{
public:
    TestStmtVisitor() = default;
    virtual ~TestStmtVisitor() = default;

    virtual void visitBlockStmt(const BlockStmt &) override { visited_ = true; }
    virtual void visitClassStmt(const ClassStmt &) override { visited_ = true; }
    virtual void visitExpressionStmt(const ExpressionStmt &) override { visited_ = true; }
    virtual void visitForEachStmt(const ForEachStmt &) override { visited_ = true; }
    virtual void visitForRangeStmt(const ForRangeStmt &) override { visited_ = true; }
    virtual void visitFunctionStmt(const FunctionStmt &) override { visited_ = true; }
    virtual void visitIfStmt(const IfStmt &) override { visited_ = true; }
    virtual void visitVarStmt(const VarStmt &) override { visited_ = true; }

    bool visited() const { return visited_; }

private:
    bool visited_;
};

#endif