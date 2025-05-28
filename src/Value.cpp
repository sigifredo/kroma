

// own
#include <Value.hpp>

Value::Value() : data(std::monostate{}) {}
Value::Value(const double &number) : data(number) {}
Value::Value(const int &number) : data(static_cast<double>(number)) {}
Value::Value(const std::string &str) : data(str) {}
Value::Value(const char *cstr) : data(std::string(cstr)) {}
Value::Value(const bool &boolean) : data(boolean) {}

bool Value::asBool() const
{
    if (!isBool())
        throw std::runtime_error("Value is not a boolean");

    return std::get<bool>(data);
}

double Value::asNumber() const
{
    if (!isNumber())
        throw std::runtime_error("Value is not a number");

    return std::get<double>(data);
}

const std::string &Value::asString() const
{
    if (!isString())
        throw std::runtime_error("Value is not a string");

    return std::get<std::string>(data);
}

std::string Value::toString() const
{
    if (isNull())
        return "null";

    if (isBool())
        return asBool() ? "true" : "false";

    if (isNumber())
    {
        std::string result = std::to_string(asNumber());
        result.erase(result.find_last_not_of('0') + 1);

        if (result.back() == '.')
        {
            result.pop_back();
        }

        return result;
    }

    if (isString())
        return asString();

    return "unknown";
}

bool Value::operator==(const Value &other) const
{
    return data == other.data;
}

std::ostream &operator<<(std::ostream &os, const Value &val)
{
    os << val.toString();
    return os;
}
