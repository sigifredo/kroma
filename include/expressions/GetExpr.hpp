

#ifndef EXPRESSIONS_GETEXPR_HPP
#define EXPRESSIONS_GETEXPR_HPP

// Own
#include <expressions/Expr.hpp>

class GetExpr : public Expr
{
public:
    GetExpr(std::unique_ptr<Expr> object, const Token &name) : object_(std::move(object)), name_(name) {}

    std::string accept(const ExprVisitor &visitor) const override;

    const Expr *object() const;
    const Token &name() const;

private:
    std::unique_ptr<Expr> object_;
    Token name_;
};

inline std::string GetExpr::accept(const ExprVisitor &visitor) const { return visitor.visitGetExpr(*this); }
inline const Expr *GetExpr::object() const { return object_.get(); }
inline const Token &GetExpr::name() const { return name_; }

#endif
