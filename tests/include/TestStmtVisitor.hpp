

#ifndef TEST_TESTSTMTVISITOR_HPP
#define TEST_TESTSTMTVISITOR_HPP

#include <stmt/StmtVisitor.hpp>

class TestStmtVisitor : public StmtVisitor
{
public:
    TestStmtVisitor() = default;
    virtual ~TestStmtVisitor() = default;

    virtual std::string visitBlockStmt(const BlockStmt &) override { return "visited"; }
    virtual std::string visitClassStmt(const ClassStmt &) override { return "visited"; }
    virtual std::string visitExpressionStmt(const ExpressionStmt &) const override { return "visited"; }
    virtual std::string visitForEachStmt(const ForEachStmt &) override { return "visited"; }
    virtual std::string visitForRangeStmt(const ForRangeStmt &) override { return "visited"; }
    virtual std::string visitFunctionStmt(const FunctionStmt &) override { return "visited"; }
    virtual std::string visitIfStmt(const IfStmt &) const override { return "visited"; }
    virtual std::string visitReturnStmt(const ReturnStmt &) const override { return "visited"; };
    virtual std::string visitVarStmt(const VarStmt &) const override { return "visited"; }
};

#endif