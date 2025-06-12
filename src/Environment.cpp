
// own
#include <Environment.hpp>
#include <RuntimeError.hpp>

void Environment::assign(const std::string &name, Value value)
{
    if (auto it = values_.find(name); it != values_.end())
    {
        if (it->second.isConst)
        {
            throw RuntimeError("No se puede reasignar la constante '" + name + "'.");
        }

        it->second.value = std::move(value);
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
        std::cout << key << ":" << ((val.isConst) ? "const" : "let") << " = " << val.value << ", ";
    }

    std::cout << "}" << std::endl;

    if (enclosing_)
    {
        std::cout << "Enclosing -> ";
        enclosing_->debugPrint();
    }
}

void Environment::define(const std::string &name, Value value, bool isConst)
{
    if (values_.count(name))
    {
        throw RuntimeError("Variable '" + name + "' ya ha sido declarada en este scope.");
    }

    values_[name] = VariableBinding{std::move(value), isConst};
}

Value Environment::get(const std::string &name) const
{
    if (auto it = values_.find(name); it != values_.end())
    {
        return it->second.value;
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
