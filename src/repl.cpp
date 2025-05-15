

// Own
#include <DummyListener.hpp>
#include <REPL.hpp>

// std
#include <iostream>

int main()
{
    std::cout << "Welcome to kroma (Ctrl+D to exit)\n";

    REPL repl;
    DummyListener dl;

    repl.addListener(&dl);
    repl.run();

    return 0;
}
