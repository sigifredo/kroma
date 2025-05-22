

#ifndef UNARYEXPR_HPP
#define UNARYEXPR_HPP

// Own
#include <Expr.hpp>

// std
#include <memory>

class UnaryExpr : public Expr
{
public:
    UnaryExpr(const std::string &o, std::shared_ptr<Expr> r);

    std::string accept(ExprVisitor &visitor) const;

private:
    std::string op;
    std::shared_ptr<Expr> right;
};

#endif