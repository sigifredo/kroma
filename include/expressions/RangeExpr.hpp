

#ifndef EXPRESSIONS_RANGEEXPR_HPP
#define EXPRESSIONS_RANGEEXPR_HPP

// own
#include <expressions/Expr.hpp>

class RangeExpr : public Expr
{
public:
    RangeExpr(std::unique_ptr<Expr> start,
              std::unique_ptr<Expr> end,
              std::unique_ptr<Expr> step = nullptr)
        : start_(std::move(start)), end_(std::move(end)), step_(std::move(step)) {};

    std::string accept(const ExprVisitor &visitor) const override;
    Value accept(InterpreterVisitor &visitor) const override;

    const Expr *start() const;
    const Expr *end() const;
    const Expr *step() const;

private:
    std::unique_ptr<Expr> start_;
    std::unique_ptr<Expr> end_;
    std::unique_ptr<Expr> step_;
};

inline std::string RangeExpr::accept(const ExprVisitor &visitor) const { return visitor.visitRangeExpr(*this); }
#warning "Implementar"
inline Value RangeExpr::accept(InterpreterVisitor &visitor) const { return "visitor.visitRangeExpr(*this)"; }
inline const Expr *RangeExpr::start() const { return start_.get(); }
inline const Expr *RangeExpr::end() const { return end_.get(); }
inline const Expr *RangeExpr::step() const { return step_.get(); }

#endif
