

#ifndef EXPRESSIONS_EXPRVISITOR_HPP
#define EXPRESSIONS_EXPRVISITOR_HPP

// std
#include <string>

class AssignExpr;
class BinaryExpr;
class CallExpr;
class FStringExpr;
class GetExpr;
class GroupingExpr;
class IndexExpr;
class ListExpr;
class LiteralExpr;
class LogicalExpr;
class RangeExpr;
class UnaryExpr;
class VariableExpr;

class ExprVisitor
{
public:
    ExprVisitor() = default;
    virtual ~ExprVisitor() = default;

    virtual std::string visit(const AssignExpr &expr) const = 0;
    virtual std::string visit(const BinaryExpr &expr) const = 0;
    virtual std::string visit(const CallExpr &expr) const = 0;
    virtual std::string visit(const FStringExpr &expr) const = 0;
    virtual std::string visit(const GetExpr &expr) const = 0;
    virtual std::string visit(const GroupingExpr &expr) const = 0;
    virtual std::string visit(const IndexExpr &expr) const = 0;
    virtual std::string visit(const ListExpr &expr) const = 0;
    virtual std::string visit(const LiteralExpr &expr) const = 0;
    virtual std::string visit(const LogicalExpr &expr) const = 0;
    virtual std::string visit(const RangeExpr &expr) const = 0;
    virtual std::string visit(const UnaryExpr &expr) const = 0;
    virtual std::string visit(const VariableExpr &expr) const = 0;
};

#endif