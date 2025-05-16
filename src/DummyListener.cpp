

// Own
#include <DummyListener.hpp>
#include <Scanner.hpp>

// std
#include <iostream>

DummyListener::DummyListener()
{
    hadError = false;
}

void DummyListener::onCommand(const std::string &command)
{
    if (!command.empty())
    {
        std::cout << "[DummyListener] Received command: " << command << std::endl;
        Scanner scanner(command);

        std::list<Token> tokens = scanner.scanTokens();

        for (auto &token : tokens)
        {
            std::cout << "Token: " << token.toString() << std::endl;
        }
    }
}

void DummyListener::error(const int &line, const std::string &message)
{
    report(line, "", message);
}

void DummyListener::report(const int &line, const std::string &where, const std::string &message)
{
    std::cerr << "[line " << line << "] Error -> " << where << ": " << message << std::endl;
    hadError = true;
}