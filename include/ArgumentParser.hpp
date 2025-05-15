

#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#include <string>
#include <unordered_map>

class ArgumentParser
{
public:
#ifdef PROJECT_NAME
    explicit ArgumentParser(int argc, char **argv, const std::string &program_name = PROJECT_NAME);
#else
    explicit ArgumentParser(int argc, char **argv, const std::string &program_name);
#endif

    void addArgument(const std::string &name,
                     const std::string &help = "",
                     bool required = false,
                     const std::string &defaultValue = "",
                     bool isFlag = false);

    void parse(int argc, char *argv[]);
    bool isSet(const std::string &name) const;
    std::string get(const std::string &name) const;

    void printHelp() const;

private:
    struct Argument
    {
        std::string name;         ///< Name of the argument.
        std::string help;         ///< Help text shown in usage.
        bool required;            ///< Whether the argument is required.
        std::string defaultValue; ///< Default value if not explicitly set.
        bool isFlag;              ///< Whether this is a flag (e.g. --verbose).
        bool set;                 ///< Whether the argument was set by the user.
        std::string value;        ///< The actual value, if set.
    };

    std::unordered_map<std::string, Argument> arguments; ///< Map of argument name to Argument struct.
    std::string programName;                             ///< Name of the program (for help messages).
};

#endif
