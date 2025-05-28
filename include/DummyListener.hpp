

#ifndef DUMMYLISTENER_HPP
#define DUMMYLISTENER_HPP

#include <CommandListener.hpp>

class DummyListener : public CommandListener
{
public:
    DummyListener();

    void onCommand(const std::string &command) override final;

private:
    bool hadError;

    void error(const int &line, const std::string &message);
    void report(const int &line, const std::string &where, const std::string &message);
};

#endif