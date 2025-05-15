

// Own
#include <DummyListener.hpp>
#include <REPL.hpp>

// std
#include <iostream>

int main()
{
    std::cout << "Bienvenido a tu REPL estilo Bash (usa Ctrl+D para salir)\n";

    REPL repl;
    DummyListener dl;

    repl.addListener(&dl);
    repl.run();

    return 0;
}
