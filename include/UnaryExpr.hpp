

#ifndef UNARYEXPR_HPP
#define UNARYEXPR_HPP

// Own
#include <Expr.hpp>
#include <Token.hpp>

// std
#include <memory>

class UnaryExpr : public Expr
{
public:
    UnaryExpr(const Token &o, std::shared_ptr<Expr> r);

    std::string accept(ExprVisitor &visitor) const;

private:
    Token op;
    std::shared_ptr<Expr> right;
};

#endif