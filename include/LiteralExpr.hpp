

#ifndef LITERALEXPR_HPP
#define LITERALEXPR_HPP

// Own
#include <Expr.hpp>

class LiteralExpr : public Expr
{
public:
    LiteralExpr(const std::string &val);

    std::string accept(ExprVisitor &visitor) const override;

private:
    std::string value;
};

#endif