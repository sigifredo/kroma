// readline
#include <readline/readline.h>
#include <readline/history.h>

// std
#include <cstdlib>
#include <iostream>
#include <string>

std::string readLine();

int main()
{
    std::cout << "Bienvenido a tu REPL estilo Bash (usa Ctrl+D para salir)\n";

    while (true)
    {
        std::string line = readLine();

        if (line.empty() && std::cin.eof())
        {
            std::cout << "\nAdiós.\n";
            break;
        }

        if (!line.empty())
        {
            add_history(line.c_str());
        }

        if (line == "exit" || line == "quit")
        {
            break;
        }

        std::cout << "→ Ejecutando: " << line << "\n";
    }

    return 0;
}

std::string readLine()
{
    char *input = readline("kroma> ");

    if (input == nullptr)
    {
        std::cin.setstate(std::ios::eofbit);

        return "";
    }
    else
    {
        std::string line(input);
        free(input);

        return line;
    }
}
