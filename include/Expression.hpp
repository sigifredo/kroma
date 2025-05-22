

#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

// Own
#include <Value.hpp>

class Expression
{
public:
    virtual ~Expression() = default;
    virtual std::string toString() const = 0;

    virtual Value evaluate() const = 0;
};

#endif
