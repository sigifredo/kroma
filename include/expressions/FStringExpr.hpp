

#ifndef EXPRESSIONS_FSTRINGEXPR_HPP
#define EXPRESSIONS_FSTRINGEXPR_HPP

// own
#include <expressions/Expr.hpp>

class FStringExpr : public Expr
{
public:
    explicit FStringExpr(std::vector<std::unique_ptr<Expr>> parts)
        : parts_(std::move(parts)) {}

    std::string accept(const ExprVisitor &visitor) const override;
    Value accept(InterpreterVisitor &visitor) const override;

    const std::vector<std::unique_ptr<Expr>> &parts() const;

private:
    std::vector<std::unique_ptr<Expr>> parts_;
};

inline std::string FStringExpr::accept(const ExprVisitor &visitor) const { return visitor.visit(*this); }
inline Value FStringExpr::accept(InterpreterVisitor &visitor) const { return visitor.visitFStringExpr(*this); }
inline const std::vector<std::unique_ptr<Expr>> &FStringExpr::parts() const { return parts_; }

#endif