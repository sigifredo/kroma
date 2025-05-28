

#ifndef EXPRESSIONS_UNARYEXPR_HPP
#define EXPRESSIONS_UNARYEXPR_HPP

// Own
#include <expressions/Expr.hpp>

class UnaryExpr : public Expr
{
public:
    UnaryExpr(const Token &o, std::unique_ptr<Expr> r) : _op(o), _right(std::move(r)) {}

    std::string accept(const ExprVisitor &visitor) const override;

    const Token &op() const;
    const Expr *right() const;

private:
    Token _op;
    std::unique_ptr<Expr> _right;
};

inline std::string UnaryExpr::accept(const ExprVisitor &visitor) const { return visitor.visitUnaryExpr(*this); }
inline const Token &UnaryExpr::op() const { return _op; }
inline const Expr *UnaryExpr::right() const { return _right.get(); }

#endif
