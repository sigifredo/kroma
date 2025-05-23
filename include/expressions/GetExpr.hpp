

#ifndef EXPRESSIONS_GETEXPR_HPP
#define EXPRESSIONS_GETEXPR_HPP

// Own
#include <expressions/Expr.hpp>

class GetExpr : public Expr
{
public:
    GetExpr(const std::shared_ptr<Expr> &object, const Token &name) : _object(object), _name(name) {}

    std::string accept(const ExprVisitor &visitor) const override { return visitor.visitGetExpr(*this); }

    const std::shared_ptr<Expr> &object() const;
    const Token &name() const;

private:
    std::shared_ptr<Expr> _object;
    Token _name;
};

inline const std::shared_ptr<Expr> &GetExpr::object() const
{
    return _object;
}

inline const Token &GetExpr::name() const
{
    return _name;
}

#endif
