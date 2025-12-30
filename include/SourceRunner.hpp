

#ifndef SOURCERUNNER_HPP
#define SOURCERUNNER_HPP

// std
#include <string>
#include <iosfwd>

class SourceRunner
{
public:
    struct Options
    {
        bool debugTokens;
        bool debugAST;

        Options() : debugTokens(false), debugAST(false) {}
    };

    explicit SourceRunner(Options opt = Options{}, std::ostream *out = nullptr, std::ostream *err = nullptr);

    int runSource(const std::string &source);
    int runFile(const std::string &path);

private:
    static std::string readFileOrThrow(const std::string &path);

    Options opt_;
    std::ostream *out_;
    std::ostream *err_;
};

#endif