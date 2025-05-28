

#ifndef RUNTIMEERROR_HPP
#define RUNTIMEERROR_HPP

class RuntimeError : public std::runtime_error
{
public:
    explicit RuntimeError(const std::string &message) : std::runtime_error(message), message_(message) {}

    const std::string &message() const noexcept;
    void print() const noexcept;

private:
    std::string message_;
};

inline const std::string &RuntimeError::message() const noexcept { return message_; }
inline void RuntimeError::print() const noexcept { std::cerr << "[Runtime Error] " << message_ << std::endl; }

#endif
