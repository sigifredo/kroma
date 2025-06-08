

#ifndef EXPRESSIONS_UNARYEXPR_HPP
#define EXPRESSIONS_UNARYEXPR_HPP

// own
#include <expressions/Expr.hpp>

class UnaryExpr : public Expr
{
public:
    UnaryExpr(const Token &o, std::unique_ptr<Expr> r) : op_(o), right_(std::move(r)) {}

    std::string accept(const ExprVisitor &visitor) const override;
    Value accept(InterpreterVisitor &visitor) const override;

    const Token &op() const;
    const Expr *right() const;

private:
    Token op_;
    std::unique_ptr<Expr> right_;
};

inline std::string UnaryExpr::accept(const ExprVisitor &visitor) const { return visitor.visitUnaryExpr(*this); }
#warning "Implementar"
inline Value UnaryExpr::accept(InterpreterVisitor &visitor) const { return "visitor.visitUnaryExpr(*this)"; }
inline const Token &UnaryExpr::op() const { return op_; }
inline const Expr *UnaryExpr::right() const { return right_.get(); }

#endif
