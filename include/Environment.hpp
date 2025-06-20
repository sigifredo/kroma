

#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

// own
#include <Value.hpp>

// std
#include <memory>
#include <unordered_map>

/**
 * @class Environment
 * @brief Manages variable contexts (scopes)
 */
class Environment : public std::enable_shared_from_this<Environment>
{
public:
    /**
     * @brief Creates a new environment.
     * @param enclosing Optional parent environment (outer scope).
     */
    explicit Environment(std::shared_ptr<Environment> enclosing = nullptr) : enclosing_(std::move(enclosing)) {}

    /**
     * @brief Updates an existing variable's value.
     * @param name Variable name.
     * @param value New value.
     * @throws RuntimeError if the variable is undefined.
     */
    void assign(const std::string &name, Value value);

    /**
     * @brief Prints the environment contents (for debugging).
     */
    void debugPrint() const;

    /**
     * @brief Defines a new variable in the current environment.
     * @param name Variable name.
     * @param value Variable value.
     * @param isConst Define if the variable is constant.
     */
    void define(const std::string &name, Value value, bool isConst);

    /**
     * @brief Retrieves a variable's value.
     * @param name Variable name.
     * @return The value associated with the variable.
     * @throws RuntimeError if the variable is undefined.
     */
    Value get(const std::string &name) const;

private:
    struct VariableBinding
    {
        Value value;
        bool isConst = false;
    };

    std::unordered_map<std::string, VariableBinding> values_; ///< Variable map.
    std::shared_ptr<Environment> enclosing_;                  ///< Optional parent scope.
};

#endif