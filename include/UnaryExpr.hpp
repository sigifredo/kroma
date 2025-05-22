

#ifndef UNARYEXPR_HPP
#define UNARYEXPR_HPP

// Own
#include <Expr.hpp>
#include <Token.hpp>

// std
#include <memory>

class UnaryExpr : public Expr
{
public:
    UnaryExpr(const Token &o, std::shared_ptr<Expr> r);

    std::string accept(ExprVisitor &visitor) override;

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