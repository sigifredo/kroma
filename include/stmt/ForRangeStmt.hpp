

#ifndef STMT_FORRANGESTMT_HPP
#define STMT_FORRANGESTMT_HPP

// own
#include <stmt/Stmt.hpp>

class ForRangeStmt : public Stmt
{
    ForRangeStmt(const Token &iterator,
                 std::unique_ptr<Expr> start,
                 std::unique_ptr<Expr> end,
                 std::unique_ptr<Stmt> body,
                 std::unique_ptr<Expr> step)
        : iterator_(iterator),
          start_(std::move(start)),
          end_(std::move(end)),
          step_(std::move(step)),
          body_(std::move(body))
    {
    }

    std::string accept(const StmtVisitor &visitor) const override;
    void accept(InterpreterVisitor &) const override {}

    const Token &iterator() const;
    const Expr *start() const;
    const Expr *end() const;
    const Expr *step() const;
    const Stmt *body() const;

private:
    Token iterator_;
    std::unique_ptr<Expr> start_;
    std::unique_ptr<Expr> end_;
    std::unique_ptr<Expr> step_;
    std::unique_ptr<Stmt> body_;
};

inline std::string ForRangeStmt::accept(const StmtVisitor &visitor) const override { return visitor.visitForRangeStmt(); }
inline const Token &ForRangeStmt::iterator() const { return iterator_; }
inline const Expr *ForRangeStmt::start() const { return start_.get(); }
inline const Expr *ForRangeStmt::end() const { return end_.get(); }
inline const Expr *ForRangeStmt::step() const { return step_.get(); }
inline const Stmt *ForRangeStmt::body() const { return body_.get(); }

#endif