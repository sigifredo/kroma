

#ifndef GROUPINGEXPR_HPP
#define GROUPINGEXPR_HPP

// Own
#include <Expr.hpp>

// std
#include <memory>

class GroupingExpr : public Expr
{
public:
    GroupingExpr(std::shared_ptr<Expr> expr);

    std::string accept(ExprVisitor &visitor) const override;

private:
    std::shared_ptr<Expr> expression;
};

#endif
