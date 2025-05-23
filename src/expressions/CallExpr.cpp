

// Own
#include <expressions/CallExpr.hpp>
#include <ExprVisitor.hpp>

CallExpr::CallExpr(std::unique_ptr<Expr> callee, const Token &paren, std::vector<std::unique_ptr<Expr>> arguments)
    : _arguments(std::move(arguments)), _callee(std::move(callee)),
      _paren(std::move(paren)) {}

std::string CallExpr::accept(ExprVisitor &visitor)
{
    return visitor.visitCallExpr(*this);
}