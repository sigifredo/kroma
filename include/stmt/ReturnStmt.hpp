

#ifndef STMT_RETURNSTMT_HPP
#define STMT_RETURNSTMT_HPP

#include <stmt/Stmt.hpp>

class ReturnStmt : public Stmt
{
public:
    ReturnStmt(const Token &keyword, std::unique_ptr<Expr> value = nullptr)
        : keyword_(keyword), value_(std::move(value)) {}

    std::string accept(StmtVisitor &visitor) const override;
    void accept(InterpreterVisitor &) const override {}

    const Token &keyword() const;
    const Expr *value() const;

private:
    Token keyword_;
    std::unique_ptr<Expr> value_;
};

inline std::string ReturnStmt::accept(StmtVisitor &visitor) const { return visitor.visitReturnStmt(*this); }
inline const Token &ReturnStmt::keyword() const { return keyword_; }
inline const Expr *ReturnStmt::value() const { return value_.get(); }

#endif