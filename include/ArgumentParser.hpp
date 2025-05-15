

#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

// std
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * @brief A general-purpose command-line argument parser similar to Python's argparse.
 */
class ArgumentParser
{
public:
    /**
     * @brief Construct a new ArgumentParser instance.
     * Automatically adds -h and --help flags.
     *
     * @param programName The name of the program (used in help output).
     */
    explicit ArgumentParser(const std::string &programName);

    /**
     * @brief Add a new argument (positional or optional).
     *
     * @param names A list of names/aliases (e.g., {"-v", "--verbose"} or {"filename"}).
     * @param help A short description of what the argument does.
     * @param required If true, the argument is required.
     * @param defaultValue A default value if the argument is not provided.
     * @param isFlag If true, this argument is a boolean flag (no value expected).
     */
    void addArgument(const std::vector<std::string> &names,
                     const std::string &help = "",
                     bool required = false,
                     const std::string &defaultValue = "",
                     bool isFlag = false);

    /**
     * @brief Parse the command-line arguments.
     *
     * @throws std::runtime_error on unknown arguments or missing values.
     */
    void parse(int argc, char *argv[]);

    /**
     * @brief Check if a flag or argument was provided explicitly.
     */
    bool isSet(const std::string &name) const;

    /**
     * @brief Get the value of an argument.
     */
    std::string get(const std::string &name) const;

    /**
     * @brief Print a help message.
     */
    void printHelp() const;

private:
    struct Argument
    {
        std::vector<std::string> names; ///< Name of the argument.
        std::string help;               ///< Help text shown in usage.
        bool required;                  ///< Whether the argument is required.
        std::string defaultValue;       ///< Default value if not explicitly set.
        bool isFlag;                    ///< Whether this is a flag (e.g. --verbose).
        bool set;                       ///< Whether the argument was set by the user.
        std::string value;              ///< The actual value, if set.
    };

    std::string programName;
    std::vector<std::shared_ptr<Argument>> argumentList;                 ///< List of all defined arguments, in the order they were added.
    std::unordered_map<std::string, std::shared_ptr<Argument>> aliasMap; ///< Maps each argument alias (e.g., "-v", "--verbose") to its corresponding Argument instance.

    void handleHelpIfRequested() const;
    void registerBuiltinHelp();
};

#endif
