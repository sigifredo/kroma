

#ifndef EXPRESSIONS_GROUPINGEXPR_HPP
#define EXPRESSIONS_GROUPINGEXPR_HPP

// own
#include <expressions/Expr.hpp>

class GroupingExpr : public Expr
{
public:
    GroupingExpr(std::unique_ptr<Expr> expr) : expression_(std::move(expr)) {};

    std::string accept(const ExprVisitor &visitor) const override;
    Value accept(InterpreterVisitor &visitor) const override;

    const Expr *expression() const;

private:
    std::unique_ptr<Expr> expression_;
};

inline std::string GroupingExpr::accept(const ExprVisitor &visitor) const { return visitor.visit(*this); }
#warning "Implementar"
inline Value GroupingExpr::accept(InterpreterVisitor &visitor) const { return Value("visitor.visitGroupingExpr(*this)"); }
inline const Expr *GroupingExpr::expression() const { return expression_.get(); }

#endif
