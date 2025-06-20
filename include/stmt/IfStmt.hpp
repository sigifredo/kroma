

#ifndef STMT_IFSTMT_HPP
#define STMT_IFSTMT_HPP

#include <expressions/Expr.hpp>
#include <stmt/Stmt.hpp>
#include <Token.hpp>

class IfStmt : public Stmt
{
public:
    IfStmt(std::unique_ptr<Expr> condition,
           std::unique_ptr<Stmt> thenBranch,
           std::unique_ptr<Stmt> elseBranch)
        : condition_(std::move(condition)),
          thenBranch_(std::move(thenBranch)),
          elseBranch_(std::move(elseBranch)) {}

    std::string accept(const StmtVisitor &visitor) const override;
    void accept(InterpreterVisitor &) const override;

    const Expr *condition() const;
    const Stmt *thenBranch() const;
    const Stmt *elseBranch() const;

private:
    std::unique_ptr<Expr> condition_;
    std::unique_ptr<Stmt> thenBranch_;
    std::unique_ptr<Stmt> elseBranch_;
};

inline std::string IfStmt::accept(const StmtVisitor &visitor) const { return visitor.visitIfStmt(*this); }
inline void IfStmt::accept(InterpreterVisitor &visitor) const { return visitor.visitIfStmt(*this); }
inline const Expr *IfStmt::condition() const { return condition_.get(); }
inline const Stmt *IfStmt::thenBranch() const { return thenBranch_.get(); }
inline const Stmt *IfStmt::elseBranch() const { return elseBranch_.get(); }

#endif