

// own
#include <DummyListener.hpp>
#include <ATSPrinter.hpp>
#include <Interpreter.hpp>
#include <Parser.hpp>
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

        try
        {
            Scanner scanner(command);
            std::vector<Token> tokens = scanner.scanTokens();
            Parser parser(tokens);
            ATSPrinter printer;
            Interpreter interpreter;

            for (auto &token : tokens)
            {
                std::cout << "Token: " << token.toString() << std::endl;
            }

            auto statements = parser.parse();

            for (const auto &stmt : statements)
            {
                std::cout << printer.print(stmt.get()) << std::endl;
            }

            interpreter.interpret(statements);
            interpreter.printVariables();
        }
        catch (const std::runtime_error &e)
        {
            std::cerr << "[Runtime Error] " << e.what() << std::endl;
        }
        catch (...)
        {
            std::cerr << "[Unknow Error] Something went wrong." << std::endl;
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