

#ifndef STMT_VARSTMT_HPP
#define STMT_VARSTMT_HPP

#include <expressions/Expr.hpp>
#include <stmt/Stmt.hpp>
#include <Token.hpp>

class VarStmt : public Stmt
{
public:
    explicit VarStmt(const Token &name,
                     std::unique_ptr<Expr> initializer,
                     const Token &modifier)
        : initializer_(std::move(initializer)),
          modifier_(modifier),
          name_(name) {}

    std::string accept(const StmtVisitor &visitor) const override;
    void accept(InterpreterVisitor &) const override;

    const Expr *initializer() const;
    const Token &modifier() const;
    const Token &name() const;

private:
    std::unique_ptr<Expr> initializer_;
    Token modifier_;
    Token name_;
};

inline std::string VarStmt::accept(const StmtVisitor &visitor) const { return visitor.visitVarStmt(*this); }
inline void VarStmt::accept(InterpreterVisitor &visitor) const { return visitor.visitVarStmt(*this); }
inline const Expr *VarStmt::initializer() const { return initializer_.get(); }
inline const Token &VarStmt::modifier() const { return modifier_; }
inline const Token &VarStmt::name() const { return name_; }

#endif