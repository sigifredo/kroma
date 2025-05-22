

// Own
#include <BinaryExpr.hpp>
#include <ExprVisitor.hpp>

BinaryExpr::BinaryExpr(std::shared_ptr<Expr> leftExpr, const Token &oper, std::shared_ptr<Expr> rightExpr) : left(leftExpr), op(oper), right(rightExpr) {}

std::string BinaryExpr::accept(ExprVisitor &visitor) const
{
    return visitor.visitBinaryExpr(*this);
}