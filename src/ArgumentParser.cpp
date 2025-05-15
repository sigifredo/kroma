

// Own
#include <ArgumentParser.hpp>
#include <Version.hpp>

// std
#include <iostream>

ArgumentParser::ArgumentParser(int argc, char **argv, const std::string &programName) : programName(programName)
{
    parse(argc, argv);
}

void ArgumentParser::addArgument(const std::string &name,
                                 const std::string &help,
                                 bool required,
                                 const std::string &defaultValue,
                                 bool isFlag)
{
    arguments[name] = Argument{name, help, required, defaultValue, isFlag, false, ""};
}

void ArgumentParser::parse(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        if (arguments.find(arg) != arguments.end())
        {
            Argument &a = arguments[arg];
            a.set = true;

            if (!a.isFlag)
            {
                if (i + 1 >= argc)
                    throw std::runtime_error("Missing value for argument: " + arg);

                a.value = argv[++i];
            }
        }
        else
        {
            for (auto &[key, a] : arguments)
            {
                if (!a.set && !a.isFlag && a.name[0] != '-')
                {
                    a.value = arg;
                    a.set = true;

                    break;
                }
            }
        }
    }

    // Check required arguments
    for (const auto &[key, a] : arguments)
    {
        if (a.required && !a.set)
        {
            throw std::runtime_error("Missing required argument: " + key);
        }
    }
}

bool ArgumentParser::isSet(const std::string &name) const
{
    auto it = arguments.find(name);
    return it != arguments.end() && it->second.set;
}

std::string ArgumentParser::get(const std::string &name) const
{
    auto it = arguments.find(name);

    if (it == arguments.end())
    {
        throw std::runtime_error("Unknown argument: " + name);
    }

    const auto &a = it->second;

    if (a.isFlag)
    {
        return a.set ? "true" : "false";
    }
    else if (a.set)
    {
        return a.value;
    }
    else
    {
        return a.defaultValue;
    }
}

void ArgumentParser::printHelp() const
{
    std::cout << "Usage: " << programName << " [options] [args]\n\n";
    std::cout << "Arguments:\n";

    for (const auto &[key, a] : arguments)
    {
        std::cout << "  " << key << "\t" << a.help;

        if (!a.defaultValue.empty())
        {
            std::cout << " (default: " << a.defaultValue << ")";
        }

        std::cout << "\n";
    }
}
