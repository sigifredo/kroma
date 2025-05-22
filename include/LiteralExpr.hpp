

#ifndef LITERALEXPR_HPP
#define LITERALEXPR_HPP

// Own
#include <Expr.hpp>
#include <Value.hpp>

class LiteralExpr : public Expr
{
public:
    LiteralExpr(const Value &val);

    std::string accept(ExprVisitor &visitor) const override;

private:
    Value value;
};

#endif