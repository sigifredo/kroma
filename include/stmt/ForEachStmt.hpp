

#ifndef STMT_FOREACHSTMT_HPP
#define STMT_FOREACHSTMT_HPP

// own
#include <stmt/Stmt.hpp>

class ForEachStmt : public Stmt
{
    ForEachStmt(const Token &iterator,
                std::unique_ptr<Expr> iterable,
                std::unique_ptr<Stmt> body)
        : iterator_(iterator),
          iterable_(std::move(iterable)),
          body_(std::move(body))
    {
    }

    std::string accept(const StmtVisitor &visitor) const override;
    void accept(InterpreterVisitor &) const override {}

    const Token &iterator() const;
    const Expr *iterable() const;
    const Stmt *body() const;

private:
    Token iterator_;
    std::unique_ptr<Expr> iterable_;
    std::unique_ptr<Stmt> body_;
};

inline std::string ForEachStmt::accept(const StmtVisitor &visitor) const override { return visitor.visitForEachStmt(); }
inline const Token &ForEachStmt::iterator() const { return iterator_; }
inline const Expr *ForEachStmt::iterable() const { return iterable_.get(); }
inline const Stmt *ForEachStmt::body() const { return body_.get(); }

#endif