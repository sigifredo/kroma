

#ifndef STMT_BLOCKSTMT_HPP
#define STMT_BLOCKSTMT_HPP

// own
#include <stmt/Stmt.hpp>

// std
#include <vector>

class BlockStmt : public Stmt
{
public:
    explicit BlockStmt(std::vector<std::unique_ptr<Stmt>> statements) : statements_(std::move(statements)) {}

    const std::vector<std::unique_ptr<Stmt>> &statements() const;

    std::string accept(const StmtVisitor &visitor) const override;
    void accept(InterpreterVisitor &visitor) const override;

private:
    std::vector<std::unique_ptr<Stmt>> statements_;
};

inline const std::vector<std::unique_ptr<Stmt>> &BlockStmt::statements() const { return statements_; }
inline std::string BlockStmt::accept(const StmtVisitor &visitor) const { return visitor.visitBlockStmt(*this); }
inline void BlockStmt::accept(InterpreterVisitor &visitor) const { return visitor.visitBlockStmt(*this); }

#endif