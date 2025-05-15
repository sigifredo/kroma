

// Own
#include <ArgumentParser.hpp>
#include <DummyListener.hpp>
#include <REPL.hpp>
#include <Version.hpp>

// std
#include <iostream>

int main(int argc, char **argv)
{
    ArgumentParser args(PROJECT_NAME);

    args.addArgument({"filename"}, "Input file to read", false);
    args.addArgument({"-v", "--verbose"}, "Enable verbose mode", false, "", true);

    try
    {
        args.parse(argc, argv);
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << "\n";
        args.printHelp();
        return 1;
    }

    std::string filename = args.get("filename");

    if (filename.empty())
    {
        std::cout << PROJECT_NAME " v" PROJECT_VERSION "\n";
        std::cout << "Welcome to kroma!\n\n";

        REPL repl;
        DummyListener dl;

        repl.addListener(&dl);
        repl.run();
    }
    else
    {
        std::cout << "Reading file: " << filename << "\n";
    }

    return 0;
}
