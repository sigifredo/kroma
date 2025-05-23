

#ifndef EXPRESSIONS_ASSIGNEXPR_HPP
#define EXPRESSIONS_ASSIGNEXPR_HPP

// Own
#include <expressions/Expr.hpp>
#include <Token.hpp>

// std
#include <memory>

class AssignExpr : public Expr
{
public:
    AssignExpr(const Token &name, const std::shared_ptr<Expr> &value) : _name(name), _value(value) {}

    std::string accept(ExprVisitor &visitor) override { return visitor.visitAssignExpr(*this); }

    const Token &name() const;
    const std::shared_ptr<Expr> value() const;

private:
    Token _name;
    std::shared_ptr<Expr> _value;
};

inline const Token &AssignExpr::name() const
{
    return _name;
}

inline const std::shared_ptr<Expr> AssignExpr::value() const
{
    return _value;
}

#endif
