

#ifndef EXPRESSION_CALLEXPR_HPP
#define EXPRESSION_CALLEXPR_HPP

// Own
#include <expressions/Expr.hpp>

// std
#include <ranges>
#include <vector>

class CallExpr : public Expr
{
public:
    CallExpr(std::unique_ptr<Expr> callee, const Token &paren, std::vector<std::unique_ptr<Expr>> arguments)
        : _arguments(std::move(arguments)), _callee(std::move(callee)), _paren(std::move(paren)) {}

    std::string accept(const ExprVisitor &visitor) const override;

    size_t argumentCount() const;
    const Expr *argument(const size_t &index) const;
    auto arguments() const;
    const Expr *callee() const;
    const Token &paren() const;

private:
    std::vector<std::unique_ptr<Expr>> _arguments;
    std::unique_ptr<Expr> _callee;
    Token _paren;
};

inline std::string CallExpr::accept(const ExprVisitor &visitor) const { return visitor.visitCallExpr(*this); }
inline size_t CallExpr::argumentCount() const { return _arguments.size(); }
inline const Expr *CallExpr::argument(const size_t &index) const { return _arguments.at(index).get(); }
inline auto CallExpr::arguments() const
{
    return _arguments | std::views::transform([](const std::unique_ptr<Expr> &arg)
                                              { return arg.get(); });
}
inline const Expr *CallExpr::callee() const { return _callee.get(); }
inline const Token &CallExpr::paren() const { return _paren; }

#endif
