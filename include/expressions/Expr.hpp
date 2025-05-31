

#ifndef EXPRESSIONS_EXPR_HPP
#define EXPRESSIONS_EXPR_HPP

// own
#include <expressions/ExprVisitor.hpp>
#include <Token.hpp>
#include <Value.hpp>

// std
#include <memory>

class ExprVisitor;

class Expr
{
public:
    virtual ~Expr() = default;

    virtual std::string accept(const ExprVisitor &visitor) const = 0;
    // virtual Value evaluate() const = 0;
    // virtual std::string toString() const = 0;
};

#endif
