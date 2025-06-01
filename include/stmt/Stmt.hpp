

#ifndef STMT_HPP
#define STMT_HPP

// own
#include <stmt/StmtVisitor.hpp>

// std
#include <memory>

class Stmt
{
public:
    virtual ~Stmt() = default;

    virtual void accept(StmtVisitor &) const = 0;
};

#endif
