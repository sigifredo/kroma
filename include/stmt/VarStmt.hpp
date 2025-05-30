

#ifndef STMT_VARSTMT_HPP
#define STMT_VARSTMT_HPP

#include <expressions/Expr.hpp>
#include <stmt/Stmt.hpp>
#include <Token.hpp>

class VarStmt : public Stmt
{
public:
    VarStmt(const Token &name,
            std::unique_ptr<Expr> initializer,
            const Token &modifier)
        : name_(name),
          initializer_(std::move(initializer)),
          modifier_(modifier) {}

    void accept(StmtVisitor &visitor) const override;

    const Token &name() const;
    const Expr *initializer() const;
    const Token &modifier() const;

private:
    Token name_;
    std::unique_ptr<Expr> initializer_;
    Token modifier_;
};

inline void VarStmt::accept(StmtVisitor &visitor) const { return visitor.visitVarStmt(*this); }
inline const Token &VarStmt::name() const { return name_; }
inline const Expr *VarStmt::initializer() const { return initializer_.get(); }
inline const Token &VarStmt::modifier() const { return modifier_; }

#endif