

#ifndef PARSEERROR_HPP
#define PARSEERROR_HPP

class ParseError : public std::runtime_error
{
public:
    explicit ParseError(const std::string &message) : std::runtime_error(message), message_(message) {}

    const std::string &message() const noexcept;
    void print() const noexcept;

private:
    std::string message_;
};

inline const std::string &ParseError::message() const noexcept { return message_; }
inline void ParseError::print() const noexcept { std::cerr << "[Runtime Error] " << message_ << std::endl; }

#endif
