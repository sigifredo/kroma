

#ifndef EXPRESSIONS_ASSIGNEXPR_HPP
#define EXPRESSIONS_ASSIGNEXPR_HPP

// Own
#include <expressions/Expr.hpp>

class AssignExpr : public Expr
{
public:
    AssignExpr(const Token &name, std::unique_ptr<Expr> value) : _name(name), _value(std::move(value)) {}

    std::string accept(const ExprVisitor &visitor) const override { return visitor.visitAssignExpr(*this); }

    const Token &name() const;
    const Expr *value() const;

private:
    Token _name;
    std::unique_ptr<Expr> _value;
};

inline const Token &AssignExpr::name() const
{
    return _name;
}

inline const Expr *AssignExpr::value() const
{
    return _value.get();
}

#endif
