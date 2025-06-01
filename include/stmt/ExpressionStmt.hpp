

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

    void accept(StmtVisitor &visitor) const override;

    const Expr *expression() const;

private:
    std::unique_ptr<Expr> expression_;
};

inline void ExpressionStmt::accept(StmtVisitor &visitor) const { visitor.visitExpressionStmt(*this); }
inline const Expr *ExpressionStmt::expression() const { return expression_.get(); }

#endif