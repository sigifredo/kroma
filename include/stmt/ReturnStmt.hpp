

#ifndef STMT_RETURNSTMT_HPP
#define STMT_RETURNSTMT_HPP

#include <stmt/Stmt.hpp>

class ReturnStmt : public Stmt
{
public:
    ReturnStmt(const Token &keyword, std::unique_ptr<Expr> value = nullptr)
        : keyword_(keyword), value_(std::move(value)) {}

    void accept(StmtVisitor &visitor) const override;

    const Token &keyword() const;
    const Expr *value() const;

private:
    Token keyword_;
    std::unique_ptr<Expr> value_;
};

inline void ReturnStmt::accept(StmtVisitor &visitor) const { visitor.visitReturnStmt(*this); }
inline const Token &ReturnStmt::keyword() const { return keyword_; }
inline const Expr *ReturnStmt::value() const { return value_.get(); }

#endif