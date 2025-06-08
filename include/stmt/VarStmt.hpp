

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
                     std::optional<Token> modifier = std::nullopt)
        : initializer_(std::move(initializer)),
          modifier_(std::move(modifier)),
          name_(name) {}

    std::string accept(StmtVisitor &visitor) const override;
    void accept(InterpreterVisitor &) const override;

    const Expr *initializer() const;
    const std::optional<Token> &modifier() const;
    const Token &name() const;

private:
    std::unique_ptr<Expr> initializer_;
    std::optional<Token> modifier_;
    Token name_;
};

inline std::string VarStmt::accept(StmtVisitor &visitor) const { return visitor.visitVarStmt(*this); }
inline void VarStmt::accept(InterpreterVisitor &visitor) const { return visitor.visitVarStmt(*this); }
inline const Expr *VarStmt::initializer() const { return initializer_.get(); }
inline const std::optional<Token> &VarStmt::modifier() const { return modifier_; }
inline const Token &VarStmt::name() const { return name_; }

#endif