

// Own
#include <LiteralExpr.hpp>
#include <ExprVisitor.hpp>

LiteralExpr::LiteralExpr(const std::string &val) : value(val) {}

std::string LiteralExpr::accept(ExprVisitor &visitor) const
{
    return visitor.visitLiteralExpr(*this);
}