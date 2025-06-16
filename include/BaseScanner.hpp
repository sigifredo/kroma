

#ifndef BASESCANNER_HPP
#define BASESCANNER_HPP

// own
#include <Token.hpp>

// std
#include <string>
#include <vector>

class BaseScanner
{
public:
    explicit BaseScanner(const std::string &src)
        : current_(0), line_(1), source_(src) {}
    virtual ~BaseScanner() = default;

    virtual std::vector<Token> scanTokens() = 0;

protected:
    char advance();
    bool isAtEnd() const;
    bool match(const char &expected);
    void newLine();
    char peek() const;
    char peekNext() const;

    size_t current() const;
    int line() const;
    const std::string &source() const;

private:
    size_t current_;
    int line_;
    std::string source_;
};

inline size_t BaseScanner::current() const { return current_; }
inline int BaseScanner::line() const { return line_; }
inline const std::string &BaseScanner::source() const { return source_; }

#endif