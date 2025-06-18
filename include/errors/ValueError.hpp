

#ifndef ERROR_VALUEERROR_HPP
#define ERROR_VALUEERROR_HPP

// std
#include <iostream>
#include <string>

class ValueError : public std::runtime_error
{
public:
    explicit ValueError(const std::string &message) : std::runtime_error("[ValueError] " + message), message_("[Value Error] " + message) {}

    const std::string &message() const noexcept;
    void print() const noexcept;

private:
    std::string message_;
};

inline const std::string &ValueError::message() const noexcept { return message_; }
inline void ValueError::print() const noexcept { std::cerr << message() << std::endl; }

#endif
