

#ifndef REPLCONTROLLER_HPP
#define REPLCONTROLLER_HPP

// own
#include <CommandListener.hpp>
#include <Interpreter.hpp>

// std
#include <memory>

class Token;

class ReplController : public CommandListener
{
public:
    ReplController() : hadError_(false), interpreter_(std::make_unique<Interpreter>()), showDebug_(false) {}

    void onCommand(const std::string &command) override final;
    void setShowDebug(const bool &showDebug);

private:
    bool hadError_;
    std::unique_ptr<Interpreter> interpreter_;
    bool showDebug_;

    void debug(const std::vector<Token> &tokens, const std::vector<std::unique_ptr<Stmt>> &stmts);
    void error(const int &line, const std::string &message);
    void report(const int &line, const std::string &where, const std::string &message);
};

inline void ReplController::setShowDebug(const bool &showDebug) { showDebug_ = showDebug; }

#endif
