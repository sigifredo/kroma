

#ifndef EXPRESSIONS_VARIABLEEXPR_HPP
#define EXPRESSIONS_VARIABLEEXPR_HPP

// Own
#include <expressions/Expr.hpp>

class VariableExpr : public Expr
{
public:
    explicit VariableExpr(const Token &name) : name_(name) {}

    std::string accept(const ExprVisitor &visitor) const override;
    const Token &name() const;

private:
    Token name_;
};

inline std::string VariableExpr::accept(const ExprVisitor &visitor) const { return visitor.visitVariableExpr(*this); }
inline const Token &VariableExpr::name() const { return name_; }

#endif
