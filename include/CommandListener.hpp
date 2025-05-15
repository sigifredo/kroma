

#ifndef COMMANDLISTENER_HPP
#define COMMANDLISTENER_HPP

#include <string>

class CommandListener
{
public:
    virtual ~CommandListener() = default;

    virtual void onCommand(const std::string &command) = 0;
};

#endif
