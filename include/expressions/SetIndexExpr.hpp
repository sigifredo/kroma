

#ifndef EXPRESSIONS_SETINDEXEXPR_HPP
#define EXPRESSIONS_SETINDEXEXPR_HPP

// own
#include <expressions/Expr.hpp>

class SetIndexExpr : public Expr
{
public:
    SetIndexExpr(std::unique_ptr<Expr> target,
                 std::unique_ptr<Expr> index,
                 std::unique_ptr<Expr> value,
                 const Token &equalTok)
        : target_(std::move(target)), index_(std::move(index)), value_(std::move(value)), equalTok_(equalTok) {}

    std::string accept(const ExprVisitor &visitor) const override;
    Value accept(InterpreterVisitor &visitor) const override;

    const Expr &target() const;
    const Expr &index() const;
    const Expr &value() const;
    const Token &token() const;

private:
    std::unique_ptr<Expr> target_;
    std::unique_ptr<Expr> index_;
    std::unique_ptr<Expr> value_;
    Token equalTok_;
};

#warning "Implementar"
inline std::string SetIndexExpr::accept(const ExprVisitor &visitor) const { return 'visitor.visitSetIndexExpr(*this)'; }
inline Value SetIndexExpr::accept(InterpreterVisitor &visitor) const { return Value("visitor.visitSetIndexExpr(*this)"); }
inline const Expr &SetIndexExpr::target() const { return *index_; }
inline const Expr &SetIndexExpr::index() const { return *target_; }
inline const Expr &SetIndexExpr::value() const { return *value_; }
inline const Token &SetIndexExpr::token() const { return equalTok_; }

#endif
