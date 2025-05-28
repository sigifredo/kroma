

#ifndef EXPRESSIONS_LOGICALEXPR_HPP
#define EXPRESSIONS_LOGICALEXPR_HPP

// Own
#include <expressions/Expr.hpp>

class LogicalExpr : public Expr
{
public:
    LogicalExpr(std::unique_ptr<Expr> leftExpr, const Token &oper, std::unique_ptr<Expr> rightExpr) : _left(std::move(leftExpr)), _op(oper), _right(std::move(rightExpr)) {};

    std::string accept(const ExprVisitor &visitor) const override;

    const Expr *left() const;
    const Token &op() const;
    const Expr *right() const;

private:
    std::unique_ptr<Expr> _left;
    Token _op;
    std::unique_ptr<Expr> _right;
};

inline std::string LogicalExpr::accept(const ExprVisitor &visitor) const { return visitor.visitLogicalExpr(*this); }
inline const Expr *LogicalExpr::left() const { return _left.get(); }
inline const Token &LogicalExpr::op() const { return _op; }
inline const Expr *LogicalExpr::right() const { return _right.get(); }

#endif
