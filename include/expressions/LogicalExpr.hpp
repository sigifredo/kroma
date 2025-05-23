

#ifndef EXPRESSIONS_LOGICALEXPR_HPP
#define EXPRESSIONS_LOGICALEXPR_HPP

// Own
#include <expressions/Expr.hpp>

class LogicalExpr : public Expr
{
public:
    LogicalExpr(const std::shared_ptr<Expr> &leftExpr, const Token &oper, std::shared_ptr<Expr> rightExpr) : _left(leftExpr), _op(oper), _right(rightExpr) {};

    std::string accept(const ExprVisitor &visitor) const override { return visitor.visitLogicalExpr(*this); }

    const std::shared_ptr<Expr> &left() const;
    const Token &op() const;
    const std::shared_ptr<Expr> &right() const;

private:
    std::shared_ptr<Expr> _left;
    Token _op;
    std::shared_ptr<Expr> _right;
};

inline const std::shared_ptr<Expr> &LogicalExpr::left() const
{
    return _left;
}

inline const Token &LogicalExpr::op() const
{
    return _op;
}

inline const std::shared_ptr<Expr> &LogicalExpr::right() const
{
    return _right;
}

#endif
