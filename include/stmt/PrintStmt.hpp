

#ifndef STMT_PRINTSTMT_HPP
#define STMT_PRINTSTMT_HPP

#include <expressions/Expr.hpp>
#include <stmt/Stmt.hpp>
#include <Token.hpp>

class PrintStmt : public Stmt
{
public:
    explicit PrintStmt(std::unique_ptr<Expr> expression)
        : expression_(std::move(expression)) {}

    const Expr *expression() const;
    std::string accept(const StmtVisitor &visitor) const override;
    void accept(InterpreterVisitor &interpreter) const override;

private:
    std::unique_ptr<Expr> expression_;
};

inline const Expr *PrintStmt::expression() const { return expression_.get(); }
inline std::string PrintStmt::accept(const StmtVisitor &visitor) const { return visitor.visitPrintStmt(*this); }
inline void PrintStmt::accept(InterpreterVisitor &interpreter) const { interpreter.visitPrintStmt(*this); }

#endif