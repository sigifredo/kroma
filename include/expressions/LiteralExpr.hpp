

#ifndef EXPRESSIONS_LITERALEXPR_HPP
#define EXPRESSIONS_LITERALEXPR_HPP

// Own
#include <expressions/Expr.hpp>
#include <Value.hpp>

class LiteralExpr : public Expr
{
public:
    LiteralExpr(const Value &val) : _value(val) {};

    std::string accept(ExprVisitor &visitor) override { return visitor.visitLiteralExpr(*this); }

    const Value &value() const;

private:
    Value _value;
};

inline const Value &LiteralExpr::value() const
{
    return _value;
}

#endif