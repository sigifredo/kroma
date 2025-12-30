

// own
#include <ArgumentParser.hpp>
#include <REPL.hpp>
#include <ReplController.hpp>
#include <SourceRunner.hpp>
#include <Version.hpp>

// std
#include <iostream>

int main(int argc, char **argv)
{
    ArgumentParser args(PROJECT_NAME);

    args.addArgument({"filename"}, "Input file to read");
    args.addArgument({"-d", "--debug"}, "Mostrar mensajes de debug", false, "", true);

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
        ReplController controller;

        controller.setShowDebug(args.isSet("-d"));

        repl.addListener(&controller);
        repl.run();
    }
    else
    {
        std::cout << "Reading file: " << filename << "\n";

        SourceRunner::Options opt;
        opt.debugTokens = args.isSet("-d");
        opt.debugAST = args.isSet("-d");

        SourceRunner runner(opt, &std::cout, &std::cerr);

        try
        {
            return runner.runFile(filename);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << "\n";
            return 1;
        }
    }

    return 0;
}
