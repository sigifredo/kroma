

// Own
#include <GroupingExpr.hpp>
#include <ExprVisitor.hpp>

GroupingExpr::GroupingExpr(std::shared_ptr<Expr> expr) : _expression(expr) {}

std::string GroupingExpr::accept(ExprVisitor &visitor)
{
    return visitor.visitGroupingExpr(*this);
}