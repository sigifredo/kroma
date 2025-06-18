

#ifndef FSTRINGERROR_HPP
#define FSTRINGERROR_HPP

// std
#include <iostream>
#include <string>

class FStringError : public std::runtime_error
{
public:
    explicit FStringError(const std::string &message) : std::runtime_error("[FStringError] " + message), message_("[FString Error] " + message) {}

    const std::string &message() const noexcept;
    void print() const noexcept;

private:
    std::string message_;
};

inline const std::string &FStringError::message() const noexcept { return message_; }
inline void FStringError::print() const noexcept { std::cerr << message() << std::endl; }

#endif
