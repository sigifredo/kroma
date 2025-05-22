

// Own
#include <UnaryExpr.hpp>
#include <ExprVisitor.hpp>

UnaryExpr::UnaryExpr(const std::string &o, std::shared_ptr<Expr> r) : op(o), right(r) {}

std::string UnaryExpr::accept(ExprVisitor &visitor) const
{
    return visitor.visitUnaryExpr(*this);
}