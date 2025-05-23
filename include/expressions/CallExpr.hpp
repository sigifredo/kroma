

#ifndef EXPRESSION_CALLEXPR_HPP
#define EXPRESSION_CALLEXPR_HPP

// Own
#include <expressions/Expr.hpp>
#include <Token.hpp>

// std
#include <memory>
#include <vector>

class CallExpr : public Expr
{
public:
    explicit CallExpr() = default;
    CallExpr(std::unique_ptr<Expr> callee, const Token &paren, std::vector<std::unique_ptr<Expr>> arguments);

    std::string accept(ExprVisitor &visitor) override;

    const std::vector<std::unique_ptr<Expr>> &arguments() const;
    const std::unique_ptr<Expr> &callee() const;
    const Token &paren() const;

private:
    std::vector<std::unique_ptr<Expr>> _arguments;
    std::unique_ptr<Expr> _callee;
    Token _paren;
};

inline const std::vector<std::unique_ptr<Expr>> &CallExpr::arguments() const
{
    return _arguments;
}

inline const std::unique_ptr<Expr> &CallExpr::callee() const
{
    return _callee;
}

inline const Token &CallExpr::paren() const
{
    return _paren;
}

#endif
