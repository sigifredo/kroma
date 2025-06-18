

#ifndef ERROR_RUNTIMEERROR_HPP
#define ERROR_RUNTIMEERROR_HPP

class RuntimeError : public std::runtime_error
{
public:
    explicit RuntimeError(const std::string &message) : std::runtime_error("[Runtime Error] " + message), message_("[Runtime Error] " + message) {}

    const std::string &message() const noexcept;
    void print() const noexcept;

private:
    std::string message_;
};

inline const std::string &RuntimeError::message() const noexcept { return message_; }
inline void RuntimeError::print() const noexcept { std::cerr << message() << std::endl; }

#endif
