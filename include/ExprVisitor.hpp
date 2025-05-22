

#ifndef EXPRVISITOR_HPP
#define EXPRVISITOR_HPP

// std
#include <string>

class BinaryExpr;
class GroupingExpr;
class LiteralExpr;
class UnaryExpr;

class ExprVisitor
{
public:
    ExprVisitor() = default;
    virtual ~ExprVisitor() = default;

    virtual std::string visitBinaryExpr(const BinaryExpr &expr) = 0;
    virtual std::string visitGroupingExpr(const GroupingExpr &expr) = 0;
    virtual std::string visitLiteralExpr(const LiteralExpr &expr) = 0;
    virtual std::string visitUnaryExpr(const UnaryExpr &expr) = 0;
};

#endif