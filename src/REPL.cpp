

// own
#include <REPL.hpp>

// readline
#include <readline/history.h>
#include <readline/readline.h>

// std
#include <atomic>
#include <csignal>
#include <iostream>

#define PROMPT_MESSAGE "kroma> "

std::atomic<bool> interrupted = false;

static void handle_sigint(int)
{
    interrupted = true;
    std::cout << "\n[KeyInterrupted] Ctrl+C ignored.\n";
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

REPL::REPL()
{
    std::signal(SIGINT, handle_sigint);
}

void REPL::addListener(CommandListener *listener)

{
    listeners.push_back(listener);
}

void REPL::run()
{
    while (true)
    {
        if (interrupted)
        {
            interrupted = false;
        }
        else
        {
            std::string line = readLine();

            if (line.empty() && std::cin.eof())
            {
                std::cout << "\nGood bye.\n";
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

            for (auto *listener : listeners)
            {
                listener->onCommand(line);
            }
        }
    }
}

std::string REPL::readLine()
{
    char *input = readline(PROMPT_MESSAGE);

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