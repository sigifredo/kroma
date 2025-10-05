

// own
#include <Value.hpp>

// own errors
#include <errors/ValueError.hpp>

Value::Value() : data_(std::monostate{}) {}
Value::Value(const double &number) : data_(number) {}
Value::Value(const int &number) : data_(static_cast<double>(number)) {}
Value::Value(const std::int64_t &number) : data_(static_cast<double>(number)) {}
Value::Value(const std::string &str) : data_(str) {}
Value::Value(const char *cstr) : data_(std::string(cstr)) {}
Value::Value(const bool &boolean) : data_(boolean) {}
Value::Value(const std::vector<Value> &list) : data_(list) {}
Value::Value(std::initializer_list<Value> list) : data_(std::vector<Value>(list)) {}

bool Value::asBool() const
{
    if (!isBool())
        throw ValueError("Value is not a boolean");

    return std::get<bool>(data_);
}

const std::vector<Value> Value::asList() const
{
    if (!isList())
        throw ValueError("Value is not a list");

    return std::get<std::vector<Value>>(data_);
}

double Value::asNumber() const
{
    if (!isNumber())
        throw ValueError("Value is not a number");

    return std::get<double>(data_);
}

const std::string &Value::asString() const
{
    if (!isString())
        throw ValueError("Value is not a string");

    return std::get<std::string>(data_);
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

    if (isList())
    {
        std::string result = "";
        const auto &list = std::get<std::vector<Value>>(data_);

        for (const auto &element : list)
        {
            if (!result.empty())
                result += ", ";

            result += element.toString();
        }

        return "[" + result + "]";
    }

    return "unknown";
}

bool Value::operator==(const Value &other) const
{
    return data_ == other.data_;
}

bool Value::operator!=(const Value &other) const
{
    return data_ != other.data_;
}

std::ostream &operator<<(std::ostream &os, const Value &val)
{
    os << val.toString();
    return os;
}
