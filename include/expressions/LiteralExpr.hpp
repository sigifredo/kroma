

#ifndef EXPRESSIONS_LITERALEXPR_HPP
#define EXPRESSIONS_LITERALEXPR_HPP

// own
#include <expressions/Expr.hpp>

class LiteralExpr : public Expr
{
public:
    LiteralExpr(const Value &val) : value_(val) {};

    std::string accept(const ExprVisitor &visitor) const override;
    Value accept(InterpreterVisitor &visitor) const override;

    const Value &value() const;

private:
    Value value_;
};

inline std::string LiteralExpr::accept(const ExprVisitor &visitor) const { return visitor.visitLiteralExpr(*this); }
#warning "Implementar"
inline Value LiteralExpr::accept(InterpreterVisitor &visitor) const { return "visitor.visitLiteralExpr(*this)"; }

inline const Value &LiteralExpr::value() const
{
    return value_;
}

#endif