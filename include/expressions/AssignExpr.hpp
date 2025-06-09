

#ifndef EXPRESSIONS_ASSIGNEXPR_HPP
#define EXPRESSIONS_ASSIGNEXPR_HPP

// own
#include <expressions/Expr.hpp>

class AssignExpr : public Expr
{
public:
    AssignExpr(const Token &name, std::unique_ptr<Expr> value) : name_(name), value_(std::move(value)) {}

    std::string accept(const ExprVisitor &visitor) const override;
    Value accept(InterpreterVisitor &visitor) const override;

    const Token &name() const;
    const Expr *value() const;

private:
    Token name_;
    std::unique_ptr<Expr> value_;
};

inline std::string AssignExpr::accept(const ExprVisitor &visitor) const { return visitor.visitAssignExpr(*this); }
inline Value AssignExpr::accept(InterpreterVisitor &visitor) const { return visitor.visitAssignExpr(*this); }
inline const Token &AssignExpr::name() const { return name_; }
inline const Expr *AssignExpr::value() const { return value_.get(); }

#endif
