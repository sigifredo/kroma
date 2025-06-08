

#ifndef UTILS_HPP
#define UTILS_HPP

// own
#include <Value.hpp>

template <class... Ts>
struct overloaded : Ts...
{
    using Ts::operator()...;
};

template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

template <typename Op>
Value binaryNumericOp(const Value &left, const Value &right, Op op)
{
    auto visitor = overloaded{
        [&](double a, double b)
        { return Value(op(a, b)); },
        [&](auto &&, auto &&) -> Value
        { throw std::runtime_error("Operands must be numbers."); }};

    return Value::visit(std::ref(visitor), left, right);
}

#endif