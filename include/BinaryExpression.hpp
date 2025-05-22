

#ifndef BINARYEXPRESSION_HPP
#define BINARYEXPRESSION_HPP

// Own
#include <Expression.hpp>
#include <Token.hpp>

// std
#include <memory>

class BinaryExpression : public Expression
{
public:
    BinaryExpression(std::shared_ptr<Expression> leftExpr, const Token &oper, std::shared_ptr<Expression> rightExpr);

private:
    std::shared_ptr<Expression> left;
    Token op;
    std::shared_ptr<Expression> right;
};

#endif
