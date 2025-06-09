

#ifndef STMT_HPP
#define STMT_HPP

// own
#include <InterpreterVisitor.hpp>
#include <stmt/StmtVisitor.hpp>

// std
#include <memory>

class Stmt
{
public:
    virtual ~Stmt() = default;

    virtual std::string accept(const StmtVisitor &) const = 0;
    virtual void accept(InterpreterVisitor &) const = 0;
};

#endif
