

#ifndef EXPRESSIONS_VARIABLEEXPR_HPP
#define EXPRESSIONS_VARIABLEEXPR_HPP

// Own
#include <expressions/Expr.hpp>
#include <Token.hpp>

class VariableExpr : public Expr
{
public:
    explicit VariableExpr(const Token &name) : _name(name) {}

    std::string accept(ExprVisitor &visitor) override;

    const Token &name() const;

private:
    Token _name;
};

inline const Token &VariableExpr::name() const
{
    return _name;
}

#endif
