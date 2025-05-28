

#ifndef EXPRESSIONS_BINARYEXPR_HPP
#define EXPRESSIONS_BINARYEXPR_HPP

// own
#include <expressions/Expr.hpp>

class BinaryExpr : public Expr
{
public:
    BinaryExpr(std::unique_ptr<Expr> leftExpr, const Token &oper, std::unique_ptr<Expr> rightExpr) : left_(std::move(leftExpr)), op_(oper), right_(std::move(rightExpr)) {};

    std::string accept(const ExprVisitor &visitor) const override;

    const Expr *left() const;
    const Token &op() const;
    const Expr *right() const;

private:
    std::unique_ptr<Expr> left_;
    Token op_;
    std::unique_ptr<Expr> right_;
};

inline std::string BinaryExpr::accept(const ExprVisitor &visitor) const { return visitor.visitBinaryExpr(*this); }
inline const Expr *BinaryExpr::left() const { return left_.get(); }
inline const Token &BinaryExpr::op() const { return op_; }
inline const Expr *BinaryExpr::right() const { return right_.get(); }

#endif
