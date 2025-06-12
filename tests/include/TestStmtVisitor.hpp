

#ifndef TEST_TESTSTMTVISITOR_HPP
#define TEST_TESTSTMTVISITOR_HPP

#include <stmt/StmtVisitor.hpp>

class TestStmtVisitor : public StmtVisitor
{
public:
    TestStmtVisitor() = default;
    virtual ~TestStmtVisitor() = default;

    std::string visitBlockStmt(const BlockStmt &) const override { return "visited"; }
    std::string visitClassStmt(const ClassStmt &) override { return "visited"; }
    std::string visitExpressionStmt(const ExpressionStmt &) const override { return "visited"; }
    std::string visitForEachStmt(const ForEachStmt &) override { return "visited"; }
    std::string visitForRangeStmt(const ForRangeStmt &) override { return "visited"; }
    std::string visitFunctionStmt(const FunctionStmt &) override { return "visited"; }
    std::string visitIfStmt(const IfStmt &) const override { return "visited"; }
    std::string visitPrintStmt(const PrintStmt &) const override { return "visited"; };
    std::string visitReturnStmt(const ReturnStmt &) const override { return "visited"; };
    std::string visitVarStmt(const VarStmt &) const override { return "visited"; }
};

#endif