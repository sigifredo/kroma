

#ifndef EXPRVISITOR_HPP
#define EXPRVISITOR_HPP

// std
#include <string>

class AssignExpr;
class BinaryExpr;
class CallExpr;
class GetExpr;
class GroupingExpr;
class LiteralExpr;
class LogicalExpr;
class UnaryExpr;
class VariableExpr;

class ExprVisitor
{
public:
    ExprVisitor() = default;
    virtual ~ExprVisitor() = default;

    virtual std::string visitAssignExpr(const AssignExpr &expr) const = 0;
    virtual std::string visitBinaryExpr(const BinaryExpr &expr) const = 0;
    virtual std::string visitCallExpr(const CallExpr &expr) const = 0;
    virtual std::string visitGetExpr(const GetExpr &expr) const = 0;
    virtual std::string visitGroupingExpr(const GroupingExpr &expr) const = 0;
    virtual std::string visitLiteralExpr(const LiteralExpr &expr) const = 0;
    virtual std::string visitLogicalExpr(const LogicalExpr &expr) const = 0;
    virtual std::string visitUnaryExpr(const UnaryExpr &expr) const = 0;
    virtual std::string visitVariableExpr(const VariableExpr &expr) const = 0;
};

#endif