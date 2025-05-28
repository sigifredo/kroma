

#ifndef EXPRESSIONS_GETEXPR_HPP
#define EXPRESSIONS_GETEXPR_HPP

// Own
#include <expressions/Expr.hpp>

class GetExpr : public Expr
{
public:
    GetExpr(std::unique_ptr<Expr> object, const Token &name) : _object(std::move(object)), _name(name) {}

    std::string accept(const ExprVisitor &visitor) const override;

    const Expr *object() const;
    const Token &name() const;

private:
    std::unique_ptr<Expr> _object;
    Token _name;
};

inline std::string GetExpr::accept(const ExprVisitor &visitor) const { return visitor.visitGetExpr(*this); }
inline const Expr *GetExpr::object() const { return _object.get(); }
inline const Token &GetExpr::name() const { return _name; }

#endif
