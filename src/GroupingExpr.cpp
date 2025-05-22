

// Own
#include <GroupingExpr.hpp>
#include <ExprVisitor.hpp>

GroupingExpr::GroupingExpr(std::shared_ptr<Expr> expr) : expression(expr) {}

std::string GroupingExpr::accept(ExprVisitor &visitor) const
{
    return visitor.visitGroupingExpr(*this);
}