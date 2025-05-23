

#ifndef EXPRESSIONS_UNARYEXPR_HPP
#define EXPRESSIONS_UNARYEXPR_HPP

// Own
#include <expressions/Expr.hpp>

class UnaryExpr : public Expr
{
public:
    UnaryExpr(const Token &o, std::shared_ptr<Expr> r) : _op(o), _right(r) {}

    std::string accept(const ExprVisitor &visitor) const override { return visitor.visitUnaryExpr(*this); }

    const Token &op() const;
    const std::shared_ptr<Expr> &right() const;

private:
    Token _op;
    std::shared_ptr<Expr> _right;
};

inline const Token &UnaryExpr::op() const
{
    return _op;
}

inline const std::shared_ptr<Expr> &UnaryExpr::right() const
{
    return _right;
}

#endif