

// Own
#include <expressions/UnaryExpr.hpp>
#include <ExprVisitor.hpp>

UnaryExpr::UnaryExpr(const Token &o, std::shared_ptr<Expr> r) : _op(o), _right(r) {}

std::string UnaryExpr::accept(ExprVisitor &visitor)
{
    return visitor.visitUnaryExpr(*this);
}