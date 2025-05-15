

// Own
#include <DummyListener.hpp>

// std
#include <iostream>

DummyListener::DummyListener()
{
}

void DummyListener::onCommand(const std::string &command)
{
    if (!command.empty())
    {
        std::cout << "[DummyListener] Received command: " << command << std::endl;
    }
}