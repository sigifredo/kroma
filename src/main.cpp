
// Own
#include <Version.hpp>
#include <Token.hpp>

// std
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>    // Para std::exit
#include <filesystem> // Desde C++17

bool hadError = false;

void error(const int &line, const std::string &message);
void report(const int &line, const std::string &where, const std::string &message);
void run(const std::string &source);
void runFile(const std::string &path);
void runPrompt();

int main(int argc, char **argv)
{
    std::printf(PROJECT_NAME ": " PROJECT_VERSION "\n");

    if (argc > 2)
    {
        std::cout << "Usage: clox [script]" << std::endl;
        exit(64);
    }
    else if (argc == 2)
    {
        runFile(argv[1]);
    }
    else
    {
        runPrompt();
    }

    return 0;
}

void error(const int &line, const std::string &message)
{
    report(line, "", message);
}

void report(const int &line, const std::string &where, const std::string &message)
{
    std::cerr << "[line " << line << "] Error " << where << ": " << message << std::endl;
    hadError = true;
}

void run(const std::string &source)
{
    // Aquí se colocaría la lógica del intérprete
    std::cout << "Running: " << source << std::endl;
}

void runFile(const std::string &path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cerr << "Could not open file: " << path << std::endl;
        exit(65);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    run(buffer.str());

    if (hadError)
    {
        exit(67);
    }
}

void runPrompt()
{
    std::string line;

    while (true)
    {
        std::cout << "> ";

        if (!std::getline(std::cin, line) || line.empty())
        {
            break;
        }

        run(line);
    }
}
