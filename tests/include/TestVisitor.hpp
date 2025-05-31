

#ifndef TEST_TESTVISITOR_HPP
#define TEST_TESTVISITOR_HPP

// own
#include <expressions/ExprVisitor.hpp>

class TestVisitor : public ExprVisitor
{
public:
    std::string visitAssignExpr(const AssignExpr &) const override { return getVisitedStr(std::string(__func__)); }
    std::string visitBinaryExpr(const BinaryExpr &) const override { return getVisitedStr(std::string(__func__)); }
    std::string visitCallExpr(const CallExpr &) const override { return getVisitedStr(std::string(__func__)); }
    std::string visitGetExpr(const GetExpr &) const override { return getVisitedStr(std::string(__func__)); }
    std::string visitGroupingExpr(const GroupingExpr &) const override { return getVisitedStr(std::string(__func__)); }
    std::string visitLiteralExpr(const LiteralExpr &) const override { return getVisitedStr(std::string(__func__)); }
    std::string visitLogicalExpr(const LogicalExpr &) const override { return getVisitedStr(std::string(__func__)); }
    std::string visitRangeExpr(const RangeExpr &) const override { return getVisitedStr(std::string(__func__)); }
    std::string visitUnaryExpr(const UnaryExpr &) const override { return getVisitedStr(std::string(__func__)); }
    std::string visitVariableExpr(const VariableExpr &) const override { return getVisitedStr(std::string(__func__)); }

private:
    std::string getVisitedStr(const std::string &functionName) const;
};

inline std::string TestVisitor::getVisitedStr(const std::string &functionName) const
{
    return functionName.substr(5, functionName.size() - 9) + "Visited";
}

#endif