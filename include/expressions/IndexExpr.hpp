

#ifndef EXPRESSIONS_INDEXEXPR_HPP
#define EXPRESSIONS_INDEXEXPR_HPP

// own
#include <expressions/Expr.hpp>

class IndexExpr : public Expr
{
public:
    IndexExpr(std::unique_ptr<Expr> target,
              std::unique_ptr<Expr> index,
              const Token &bracketTok)
        : target_(std::move(target)), index_(std::move(index)), bracketTok_(bracketTok) {}

    std::string accept(const ExprVisitor &visitor) const override;
    Value accept(InterpreterVisitor &visitor) const override;

    Expr *target() const;
    Expr *index() const;
    const Token &token() const;

private:
    std::unique_ptr<Expr> target_;
    std::unique_ptr<Expr> index_;
    Token bracketTok_;
};

#warning "Implementar"
inline std::string IndexExpr::accept(const ExprVisitor &visitor) const { return "visitor.visitIndexExpr(*this)"; }
inline Value IndexExpr::accept(InterpreterVisitor &visitor) const { return Value("visitor.visitIndexExpr(*this)"); }
inline Expr *IndexExpr::target() const { return index_.get(); }
inline Expr *IndexExpr::index() const { return target_.get(); }
inline const Token &IndexExpr::token() const { return bracketTok_; }

#endif
