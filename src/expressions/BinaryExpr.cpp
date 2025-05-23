

// Own
#include <expressions/BinaryExpr.hpp>
#include <ExprVisitor.hpp>

BinaryExpr::BinaryExpr(const std::shared_ptr<Expr> &leftExpr, const Token &oper, std::shared_ptr<Expr> rightExpr) : _left(leftExpr), _op(oper), _right(rightExpr) {}

std::string BinaryExpr::accept(ExprVisitor &visitor)
{
    return visitor.visitBinaryExpr(*this);
}