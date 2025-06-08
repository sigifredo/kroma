

#ifndef STMT_BLOCKSTMT_HPP
#define STMT_BLOCKSTMT_HPP

// own
#include <stmt/Stmt.hpp>

// std
#include <vector>

class BlockStmt : public Stmt
{
public:
    explicit BlockStmt(std::vector<std::unique_ptr<Stmt>> statements) : statements(std::move(statements)) {}

    std::string accept(StmtVisitor &visitor) const override;
    void accept(InterpreterVisitor &) const override {}

private:
    std::vector<std::unique_ptr<Stmt>> statements;
};

inline std::string BlockStmt::accept(StmtVisitor &visitor) const { return visitor.visitBlockStmt(*this); }

#endif