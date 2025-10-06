

#ifndef TEST_TESTEXPRVISITOR_HPP
#define TEST_TESTEXPRVISITOR_HPP

// own
#include <expressions/ExprVisitor.hpp>

class TestExprVisitor : public ExprVisitor
{
public:
    std::string visit(const AssignExpr &) const override { return getVisitedStr(std::string(__func__)); }
    std::string visit(const BinaryExpr &) const override { return getVisitedStr(std::string(__func__)); }
    std::string visit(const FStringExpr &) const override { return getVisitedStr(std::string(__func__)); }
    std::string visit(const CallExpr &) const override { return getVisitedStr(std::string(__func__)); }
    std::string visit(const GetExpr &) const override { return getVisitedStr(std::string(__func__)); }
    std::string visit(const GroupingExpr &) const override { return getVisitedStr(std::string(__func__)); }
    std::string visit(const IndexExpr &) const override { return getVisitedStr(std::string(__func__)); }
    std::string visit(const ListExpr &) const override { return getVisitedStr(std::string(__func__)); }
    std::string visit(const LiteralExpr &) const override { return getVisitedStr(std::string(__func__)); }
    std::string visit(const LogicalExpr &) const override { return getVisitedStr(std::string(__func__)); }
    std::string visit(const RangeExpr &) const override { return getVisitedStr(std::string(__func__)); }
    std::string visit(const UnaryExpr &) const override { return getVisitedStr(std::string(__func__)); }
    std::string visit(const VariableExpr &) const override { return getVisitedStr(std::string(__func__)); }

private:
    std::string getVisitedStr(const std::string &functionName) const;
};

inline std::string TestExprVisitor::getVisitedStr(const std::string &functionName) const
{
    return functionName.substr(5, functionName.size() - 9) + "Visited";
}

#endif