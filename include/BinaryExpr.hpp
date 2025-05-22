

#ifndef BINARYEXPR_HPP
#define BINARYEXPR_HPP

// Own
#include <Expr.hpp>
#include <Token.hpp>

// std
#include <memory>

class BinaryExpr : public Expr
{
public:
    BinaryExpr(std::shared_ptr<Expr> leftExpr, const Token &oper, std::shared_ptr<Expr> rightExpr);

    std::string accept(ExprVisitor &visitor) const override;

private:
    std::shared_ptr<Expr> left;
    Token op;
    std::shared_ptr<Expr> right;
};

#endif
