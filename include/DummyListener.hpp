

#ifndef DUMMYLISTENER_HPP
#define DUMMYLISTENER_HPP

// own
#include <CommandListener.hpp>
#include <Interpreter.hpp>

// std
#include <memory>

class DummyListener : public CommandListener
{
public:
    DummyListener() : hadError(false), interpreter_(std::make_unique<Interpreter>()) {}

    void onCommand(const std::string &command) override final;

private:
    bool hadError;
    std::unique_ptr<Interpreter> interpreter_;

    void error(const int &line, const std::string &message);
    void report(const int &line, const std::string &where, const std::string &message);
};

#endif