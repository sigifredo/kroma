

#ifndef DUMMYLISTENER_HPP
#define DUMMYLISTENER_HPP

#include <CommandListener.hpp>

class DummyListener : public CommandListener
{
public:
    DummyListener();

    void onCommand(const std::string &command) override final;
};

#endif