

// Own
#include <LiteralExpr.hpp>
#include <ExprVisitor.hpp>

LiteralExpr::LiteralExpr(const Value &val) : _value(val) {}

std::string LiteralExpr::accept(ExprVisitor &visitor)
{
    return visitor.visitLiteralExpr(*this);
}