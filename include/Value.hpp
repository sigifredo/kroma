

#ifndef VALUE_HPP
#define VALUE_HPP

// std
#include <iostream>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

class Value
{
public:
    using VariantType = std::variant<std::monostate, double, std::string, bool, std::vector<Value>>;

    Value();
    Value(const Value &other) = default;
    Value(const int &number);
    Value(const double &number);
    Value(const std::string &str);
    Value(const char *cstr);
    Value(const bool &boolean);
    Value(const std::vector<Value> &list);
    Value(std::initializer_list<Value> list);

    bool isBool() const;
    bool isList() const;
    bool isNull() const;
    bool isNumber() const;
    bool isString() const;

    bool asBool() const;
    const std::vector<Value> asList() const;
    double asNumber() const;
    const std::string &asString() const;

    std::string toString() const;

    Value &operator=(const Value &other) = default;
    bool operator==(const Value &other) const;
    bool operator!=(const Value &other) const;

    template <typename Visitor>
    static Value visit(Visitor &&visitor, const Value &left, const Value &right);
    friend std::ostream &operator<<(std::ostream &os, const Value &val);

private:
    VariantType data;
};

inline bool Value::isBool() const { return std::holds_alternative<bool>(data); }
inline bool Value::isList() const { return std::holds_alternative<std::vector<Value>>(data); }
inline bool Value::isNull() const { return std::holds_alternative<std::monostate>(data); }
inline bool Value::isNumber() const { return std::holds_alternative<double>(data); }
inline bool Value::isString() const { return std::holds_alternative<std::string>(data); }
template <typename Visitor>
inline Value Value::visit(Visitor &&visitor, const Value &left, const Value &right)
{
    return std::visit(std::forward<Visitor>(visitor), left.data, right.data);
}

#endif
