

#ifndef EXPRESSIONS_GETEXPR_HPP
#define EXPRESSIONS_GETEXPR_HPP

// Own
#include <expressions/Expr.hpp>
#include <Token.hpp>

class GetExpr : public Expr
{
public:
    GetExpr(const std::shared_ptr<Expr> &object, const Token &name) : _object(object), _name(name) {}

    std::string accept(ExprVisitor &visitor) override;

private:
    std::shared_ptr<Expr> _object;
    Token _name;
};

#endif
