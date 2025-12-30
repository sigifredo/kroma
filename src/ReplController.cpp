

// own
#include <ReplController.hpp>
#include <ATSPrinter.hpp>
#include <Parser.hpp>
#include <Scanner.hpp>

// own errors
#include <errors/ParseError.hpp>

// std
#include <iostream>

void ReplController::onCommand(const std::string &command)
{
    if (!command.empty())
    {
        try
        {
            Scanner scanner(command);
            std::vector<Token> tokens = scanner.scanTokens();
            Parser parser(tokens);
            auto statements = parser.parse();

            if (showDebug_)
            {
                std::cout << "[ReplController] Received command: " << command << std::endl;
                debug(tokens, statements);
                interpreter_->interpret(statements);
                interpreter_->printVariables();
            }
            else
                interpreter_->interpret(statements);
        }
        catch (const ParseError &e)
        {
            std::cerr << e.message() << std::endl;
        }
        catch (const std::runtime_error &e)
        {
            std::cerr << e.what() << std::endl;
        }
        catch (...)
        {
            std::cerr << "[Unknow Error] Something went wrong." << std::endl;
        }
    }
}

void ReplController::debug(const std::vector<Token> &tokens, const std::vector<std::unique_ptr<Stmt>> &stmts)
{
    ATSPrinter printer;

    for (auto &token : tokens)
    {
        std::cout << "Token: " << token.toString() << std::endl;
    }

    for (const auto &stmt : stmts)
    {
        std::cout << printer.print(stmt.get()) << std::endl;
    }
}

void ReplController::error(const int &line, const std::string &message)
{
    report(line, "", message);
}

void ReplController::report(const int &line, const std::string &where, const std::string &message)
{
    std::cerr << "[line " << line << "] Error -> " << where << ": " << message << std::endl;
    hadError_ = true;
}