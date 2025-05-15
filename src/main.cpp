

// Own
#include <DummyListener.hpp>
#include <REPL.hpp>
#include <Version.hpp>

// std
#include <iostream>

int main()
{
    std::cout << PROJECT_NAME " v" PROJECT_VERSION "\n";
    std::cout << "Welcome to kroma!\n";

    REPL repl;
    DummyListener dl;

    repl.addListener(&dl);
    repl.run();

    return 0;
}
