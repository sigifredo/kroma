

#ifndef EXPRESSIONS_BINARYEXPR_HPP
#define EXPRESSIONS_BINARYEXPR_HPP

// Own
#include <expressions/Expr.hpp>

class BinaryExpr : public Expr
{
public:
    BinaryExpr(std::unique_ptr<Expr> leftExpr, const Token &oper, std::unique_ptr<Expr> rightExpr) : _left(std::move(leftExpr)), _op(oper), _right(std::move(rightExpr)) {};

    std::string accept(const ExprVisitor &visitor) const override;

    const Expr *left() const;
    const Token &op() const;
    const Expr *right() const;

private:
    std::unique_ptr<Expr> _left;
    Token _op;
    std::unique_ptr<Expr> _right;
};

inline std::string BinaryExpr::accept(const ExprVisitor &visitor) const { return visitor.visitBinaryExpr(*this); }
inline const Expr *BinaryExpr::left() const { return _left.get(); }
inline const Token &BinaryExpr::op() const { return _op; }
inline const Expr *BinaryExpr::right() const { return _right.get(); }

#endif
