

// own
#include <SourceRunner.hpp>
#include <Interpreter.hpp>
#include <Parser.hpp>
#include <Scanner.hpp>

// std
#include <fstream>
#include <sstream>

SourceRunner::SourceRunner(Options opt, std::ostream *out, std::ostream *err)
    : opt_(opt), out_(out), err_(err) {}

int SourceRunner::runSource(const std::string &source)
{
    Scanner scanner(source);
    auto tokens = scanner.scanTokens();

    if (opt_.debugTokens && out_)
    {
        for (const auto &t : tokens)
            (*out_) << t.toString() << "\n"; // ajusta a tu API
    }

    Parser parser(tokens);
    auto statements = parser.parse();

    if (opt_.debugAST && out_)
    {
        // imprime AST si tienes printer/visitor
    }

    Interpreter interpreter;
    interpreter.interpret(statements);
    return 0;
}

int SourceRunner::runFile(const std::string &path)
{
    return runSource(readFileOrThrow(path));
}

std::string SourceRunner::readFileOrThrow(const std::string &path)
{
    std::ifstream in(path, std::ios::binary);

    if (!in)
        throw std::runtime_error("Cannot open file: " + path);

    std::ostringstream ss;
    ss << in.rdbuf();

    return ss.str();
}