

#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

// Own
#include <Value.hpp>

class ExprVisitor;

class Expr
{
public:
    virtual ~Expr() = default;

    virtual std::string accept(ExprVisitor &visitor) = 0;
    // virtual Value evaluate() const = 0;
    // virtual std::string toString() const = 0;
};

#endif
