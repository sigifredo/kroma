

#ifndef FSTRINGSCANNER_HPP
#define FSTRINGSCANNER_HPP

// own
#include <BaseScanner.hpp>

// std
#include <list>

class FStringScanner : public BaseScanner
{
public:
    explicit FStringScanner(const std::string &src) : BaseScanner(src) {}

    std::vector<Token> scanTokens() override;

private:
    std::list<Token> tokens;
};

#endif