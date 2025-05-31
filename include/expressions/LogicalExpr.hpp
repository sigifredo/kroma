

#ifndef EXPRESSIONS_LOGICALEXPR_HPP
#define EXPRESSIONS_LOGICALEXPR_HPP

// own
#include <expressions/Expr.hpp>

class LogicalExpr : public Expr
{
public:
    LogicalExpr(std::unique_ptr<Expr> leftExpr,
                const Token &oper,
                std::unique_ptr<Expr> rightExpr)
        : left_(std::move(leftExpr)), op_(oper), right_(std::move(rightExpr)) {};

    std::string accept(const ExprVisitor &visitor) const override;

    const Expr *left() const;
    const Token &op() const;
    const Expr *right() const;

private:
    std::unique_ptr<Expr> left_;
    Token op_;
    std::unique_ptr<Expr> right_;
};

inline std::string LogicalExpr::accept(const ExprVisitor &visitor) const { return visitor.visitLogicalExpr(*this); }
inline const Expr *LogicalExpr::left() const { return left_.get(); }
inline const Token &LogicalExpr::op() const { return op_; }
inline const Expr *LogicalExpr::right() const { return right_.get(); }

#endif
