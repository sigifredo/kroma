

#ifndef VALUE_HPP
#define VALUE_HPP

// std
#include <iostream>
#include <stdexcept>
#include <string>
#include <variant>

class Value
{
public:
    using VariantType = std::variant<std::monostate, double, std::string, bool>;

    Value();
    Value(const Value &other) = default;
    Value(const double &number);
    Value(const std::string &str);
    Value(const char *cstr);
    Value(const bool &boolean);

    bool isBool() const;
    bool isNull() const;
    bool isNumber() const;
    bool isString() const;

    bool asBool() const;
    double asNumber() const;
    const std::string &asString() const;

    std::string toString() const;

    Value &operator=(const Value &other) = default;
    bool operator==(const Value &other) const;

    friend std::ostream &operator<<(std::ostream &os, const Value &val);

private:
    VariantType data;
};

inline bool Value::isNull() const { return std::holds_alternative<std::monostate>(data); }
inline bool Value::isNumber() const { return std::holds_alternative<double>(data); }
inline bool Value::isString() const { return std::holds_alternative<std::string>(data); }
inline bool Value::isBool() const { return std::holds_alternative<bool>(data); }

#endif
