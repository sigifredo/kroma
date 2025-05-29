

#ifndef STMT_HPP
#define STMT_HPP

// std
#include <memory>

class StmtVisitor;

class Stmt
{
public:
    virtual ~Stmt() = default;

    virtual void accept(StmtVisitor &) const = 0;
};

#endif
