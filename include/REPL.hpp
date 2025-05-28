

#ifndef REPL_HPP
#define REPL_HPP

// Own
#include <CommandListener.hpp>

// std
#include <vector>

class REPL
{
public:
    REPL();

    void addListener(CommandListener *listener);
    void run();

private:
    std::vector<CommandListener *> listeners;

    std::string readLine();
};

#endif