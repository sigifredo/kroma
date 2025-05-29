

#ifndef STMT_CLASSSTMT_HPP
#define STMT_CLASSSTMT_HPP

// own
#include <expressions/Expr.hpp>
#include <stmt/FunctionStmt.hpp>
#include <stmt/Stmt.hpp>
#include <stmt/Stmt.hpp>
#include <stmt/VarStmt.hpp>
#include <Token.hpp>

// std
#include <vector>

class ClassStmt : public Stmt
{
public:
    ClassStmt(Token name,
              std::unique_ptr<Expr> superclass,
              std::vector<std::unique_ptr<VarStmt>> fields,
              std::vector<std::unique_ptr<FunctionStmt>> methods,
              std::vector<Token> modifiers)
        : name(std::move(name)),
          superclass(std::move(superclass)),
          fields(std::move(fields)),
          methods(std::move(methods)),
          modifiers(std::move(modifiers)) {}

    void accept(StmtVisitor &visitor) const override;

private:
    Token name;
    std::unique_ptr<Expr> superclass;
    std::vector<std::unique_ptr<VarStmt>> fields;
    std::vector<std::unique_ptr<FunctionStmt>> methods;
    std::vector<Token> modifiers;
};

inline void ClassStmt::accept(StmtVisitor &visitor) const { visitor.visitClassStmt(*this); }

#endif