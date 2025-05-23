

#ifndef EXPRESSIONS_BINARYEXPR_HPP
#define EXPRESSIONS_BINARYEXPR_HPP

// Own
#include <expressions/Expr.hpp>
#include <Token.hpp>

// std
#include <memory>

class BinaryExpr : public Expr
{
public:
    BinaryExpr(const std::shared_ptr<Expr> &leftExpr, const Token &oper, std::shared_ptr<Expr> rightExpr) : _left(leftExpr), _op(oper), _right(rightExpr) {};

    std::string accept(ExprVisitor &visitor) override { return visitor.visitBinaryExpr(*this); }

    const std::shared_ptr<Expr> &left() const;
    const Token &op() const;
    const std::shared_ptr<Expr> &right() const;

private:
    std::shared_ptr<Expr> _left;
    Token _op;
    std::shared_ptr<Expr> _right;
};

inline const std::shared_ptr<Expr> &BinaryExpr::left() const
{
    return _left;
}

inline const Token &BinaryExpr::op() const
{
    return _op;
}

inline const std::shared_ptr<Expr> &BinaryExpr::right() const
{
    return _right;
}

#endif
