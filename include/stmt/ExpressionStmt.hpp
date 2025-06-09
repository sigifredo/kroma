

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

    std::string accept(const StmtVisitor &visitor) const override;
    void accept(InterpreterVisitor &visitor) const override;

    const Expr *expression() const;

private:
    std::unique_ptr<Expr> expression_;
};

inline std::string ExpressionStmt::accept(const StmtVisitor &visitor) const { return visitor.visitExpressionStmt(*this); }
inline void ExpressionStmt::accept(InterpreterVisitor &visitor) const { return visitor.visitExpressionStmt(*this); }
inline const Expr *ExpressionStmt::expression() const { return expression_.get(); }

#endif