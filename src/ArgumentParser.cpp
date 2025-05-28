

// own
#include <ArgumentParser.hpp>

// std
#include <cstdlib>
#include <iostream>
#include <stdexcept>

ArgumentParser::ArgumentParser(const std::string &programName)
    : programName(programName)
{
    registerBuiltinHelp();
}

void ArgumentParser::addArgument(const std::vector<std::string> &names,
                                 const std::string &help,
                                 bool required,
                                 const std::string &defaultValue,
                                 bool isFlag)
{
    auto arg = std::make_shared<Argument>(Argument{names, help, required, defaultValue, isFlag, false, ""});

    for (const auto &name : names)
    {
        if (aliasMap.count(name))
        {
            throw std::invalid_argument("Duplicate argument name: " + name);
        }

        aliasMap[name] = arg;
    }

    argumentList.push_back(arg);
}

void ArgumentParser::registerBuiltinHelp()
{
    addArgument({"-h", "--help"}, "Show this help message and exit", false, "", true);
}

void ArgumentParser::parse(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        std::string token = argv[i];

        if (aliasMap.count(token))
        {
            auto &arg = aliasMap[token];
            arg->set = true;

            if (!arg->isFlag)
            {
                if (i + 1 >= argc)
                {
                    throw std::runtime_error("Missing value for argument: " + token);
                }

                arg->value = argv[++i];
            }
        }
        else
        {
            // Try assigning to positional (non-flag, no dashes)
            bool matched = false;

            for (auto &arg : argumentList)
            {
                if (arg->names.size() == 1 && arg->names[0][0] != '-' && !arg->set)
                {
                    arg->value = token;
                    arg->set = true;
                    matched = true;

                    break;
                }
            }

            if (!matched)
            {
                throw std::runtime_error("Unknown argument: " + token);
            }
        }
    }

    handleHelpIfRequested();

    // Validate required arguments
    for (const auto &arg : argumentList)
    {
        if (arg->required && !arg->set)
        {
            throw std::runtime_error("Missing required argument: " + arg->names[0]);
        }
    }
}

void ArgumentParser::handleHelpIfRequested() const
{
    auto it = aliasMap.find("--help");

    if (it != aliasMap.end() && it->second->set)
    {
        printHelp();
        std::exit(0);
    }

    it = aliasMap.find("-h");

    if (it != aliasMap.end() && it->second->set)
    {
        printHelp();
        std::exit(0);
    }
}

bool ArgumentParser::isSet(const std::string &name) const
{
    auto it = aliasMap.find(name);
    return it != aliasMap.end() && it->second->set;
}

std::string ArgumentParser::get(const std::string &name) const
{
    auto it = aliasMap.find(name);

    if (it == aliasMap.end())
    {
        throw std::runtime_error("Unknown argument: " + name);
    }

    const auto &arg = it->second;
    if (arg->isFlag)
    {
        return arg->set ? "true" : "false";
    }
    else if (arg->set)
    {
        return arg->value;
    }
    else
    {
        return arg->defaultValue;
    }
}

void ArgumentParser::printHelp() const
{
    std::cout << "Usage: " << programName << " [options] [args]\n\n";
    std::cout << "Arguments:\n";

    for (const auto &arg : argumentList)
    {
        std::cout << "  ";
        for (size_t i = 0; i < arg->names.size(); ++i)
        {
            std::cout << arg->names[i];
            if (i < arg->names.size() - 1)
                std::cout << ", ";
        }
        std::cout << "\t" << arg->help;
        if (!arg->defaultValue.empty())
            std::cout << " (default: " << arg->defaultValue << ")";
        if (arg->required)
            std::cout << " [required]";
        std::cout << "\n";
    }
}
