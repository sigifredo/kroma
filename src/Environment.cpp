
// own
#include <Environment.hpp>
#include <RuntimeError.hpp>

void Environment::assign(const std::string &name, Value value)
{
    if (auto it = values_.find(name); it != values_.end())
    {
        it->second = std::move(value);
    }
    else if (enclosing_)
    {
        enclosing_->assign(name, std::move(value));
    }
    else
    {
        throw RuntimeError("Undefined variable '" + name + "'.");
    }
}

void Environment::debugPrint() const
{
    std::cout << "{ ";

    for (const auto &[key, val] : values_)
    {
        std::cout << key << ": " << val;
    }

    std::cout << "}" << std::endl;

    if (enclosing_)
    {
        std::cout << "Enclosing -> ";
        enclosing_->debugPrint();
    }
}

void Environment::define(const std::string &name, Value value)
{
    values_[name] = std::move(value);
}

Value Environment::get(const std::string &name) const
{
    if (auto it = values_.find(name); it != values_.end())
    {
        return it->second;
    }
    else if (enclosing_)
    {
        return enclosing_->get(name);
    }
    else
    {
        throw RuntimeError("Variable \"" + name + "\" is not defined.");
    }
}
