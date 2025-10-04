

#ifndef EXPRESSION_CALLEXPR_HPP
#define EXPRESSION_CALLEXPR_HPP

// own
#include <expressions/Expr.hpp>

// std
#include <ranges>
#include <vector>

class CallExpr : public Expr
{
public:
    CallExpr(std::unique_ptr<Expr> callee, const Token &paren, std::vector<std::unique_ptr<Expr>> arguments)
        : arguments_(std::move(arguments)), callee_(std::move(callee)), paren_(std::move(paren)) {}

    std::string accept(const ExprVisitor &visitor) const override;
    Value accept(InterpreterVisitor &visitor) const override;

    size_t argumentCount() const;
    const Expr *argument(const size_t &index) const;
    auto arguments() const;
    const Expr *callee() const;
    const Token &paren() const;

private:
    std::vector<std::unique_ptr<Expr>> arguments_;
    std::unique_ptr<Expr> callee_;
    Token paren_;
};

inline std::string CallExpr::accept(const ExprVisitor &visitor) const { return visitor.visitCallExpr(*this); }
#warning "Implementar"
inline Value CallExpr::accept(InterpreterVisitor &) const { return Value("visitor.visitCallExpr(*this)"); }
inline size_t CallExpr::argumentCount() const { return arguments_.size(); }
inline const Expr *CallExpr::argument(const size_t &index) const { return arguments_.at(index).get(); }
inline auto CallExpr::arguments() const
{
    return arguments_ | std::views::transform([](const std::unique_ptr<Expr> &arg)
                                              { return arg.get(); });
}
inline const Expr *CallExpr::callee() const { return callee_.get(); }
inline const Token &CallExpr::paren() const { return paren_; }

#endif
