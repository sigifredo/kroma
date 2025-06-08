

#ifndef STMT_EXPRESSIONSTMT_HPP
#define STMT_EXPRESSIONSTMT_HPP

// own
#include <stmt/Stmt.hpp>
#include <stmt/StmtVisitor.hpp>

class ExpressionStmt : public Stmt
{
public:
    explicit ExpressionStmt(std::unique_ptr<Expr> expression)
        : expression_(std::move(expression)) {}

    std::string accept(StmtVisitor &visitor) const override;
    void accept(InterpreterVisitor &) const override {}

    const Expr *expression() const;

private:
    std::unique_ptr<Expr> expression_;
};

inline std::string ExpressionStmt::accept(StmtVisitor &visitor) const { return visitor.visitExpressionStmt(*this); }
inline const Expr *ExpressionStmt::expression() const { return expression_.get(); }

#endif