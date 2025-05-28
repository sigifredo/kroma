

#ifndef EXPRESSIONS_LITERALEXPR_HPP
#define EXPRESSIONS_LITERALEXPR_HPP

// own
#include <expressions/Expr.hpp>

class LiteralExpr : public Expr
{
public:
    LiteralExpr(const Value &val) : value_(val) {};

    std::string accept(const ExprVisitor &visitor) const override { return visitor.visitLiteralExpr(*this); }

    const Value &value() const;

private:
    Value value_;
};

inline const Value &LiteralExpr::value() const
{
    return value_;
}

#endif