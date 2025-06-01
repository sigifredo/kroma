

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

    void accept(StmtVisitor &visitor) const override;

private:
    std::vector<std::unique_ptr<Stmt>> statements;
};

inline void BlockStmt::accept(StmtVisitor &visitor) const { visitor.visitBlockStmt(*this); }

#endif