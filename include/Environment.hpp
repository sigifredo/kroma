

#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

// Own
#include <Value.hpp>

// std
#include <unordered_map>
#include <memory>

class Environment : public std::enable_shared_from_this<Environment>
{
public:
    explicit Environment(std::shared_ptr<Environment> enclosing = nullptr) : enclosing_(std::move(enclosing)) {}

    void assign(const std::string &name, Value value);
    void debugPrint() const;
    void define(const std::string &name, Value value);
    Value get(const std::string &name) const;

private:
    std::unordered_map<std::string, Value> values_;
    std::shared_ptr<Environment> enclosing_;
};

#endif