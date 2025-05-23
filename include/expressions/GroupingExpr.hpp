

#ifndef EXPRESSIONS_GROUPINGEXPR_HPP
#define EXPRESSIONS_GROUPINGEXPR_HPP

// Own
#include <expressions/Expr.hpp>

// std
#include <memory>

class GroupingExpr : public Expr
{
public:
    GroupingExpr(std::shared_ptr<Expr> expr) : _expression(expr) {};

    std::string accept(ExprVisitor &visitor) override { return visitor.visitGroupingExpr(*this); }

    const std::shared_ptr<Expr> expression() const;

private:
    std::shared_ptr<Expr> _expression;
};

inline const std::shared_ptr<Expr> GroupingExpr::expression() const
{
    return _expression;
}

#endif
