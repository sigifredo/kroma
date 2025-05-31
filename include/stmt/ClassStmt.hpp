

#ifndef STMT_CLASSSTMT_HPP
#define STMT_CLASSSTMT_HPP

// own
#include <expressions/Expr.hpp>
#include <stmt/FunctionStmt.hpp>
#include <stmt/Stmt.hpp>
#include <stmt/VarStmt.hpp>
#include <Token.hpp>

// std
#include <ranges>
#include <vector>

class ClassStmt : public Stmt
{
public:
    ClassStmt(Token name,
              std::unique_ptr<Expr> superclass = nullptr,
              std::vector<std::unique_ptr<VarStmt>> fields = {},
              std::vector<std::unique_ptr<FunctionStmt>> methods = {},
              const std::vector<Token> &modifiers = {})
        : name_(std::move(name)),
          superclass_(std::move(superclass)),
          fields_(std::move(fields)),
          methods_(std::move(methods)),
          modifiers_(std::move(modifiers)) {}

    void accept(const StmtVisitor &visitor) const override;

    auto fields() const;
    auto methods() const;
    const std::vector<Token> &modifiers() const;
    const Token &name() const;

private:
    std::vector<std::unique_ptr<VarStmt>> fields_;
    std::vector<std::unique_ptr<FunctionStmt>> methods_;
    std::vector<Token> modifiers_;
    Token name_;
    std::unique_ptr<Expr> superclass_;
};

inline void ClassStmt::accept(StmtVisitor &visitor) const { visitor.visitClassStmt(*this); }
inline auto ClassStmt::fields() const
{
    return fields_ | std::views::transform([](const unique_ptr<Expr> &arg)
                                           { return arg.get(); });
}
inline auto ClassStmt::methods() const
{
    return methods_ | std::views::transform([](const unique_ptr<Expr> &arg)
                                            { return arg.get(); })
}
inline std::vector<Token> &ClassStmt::modifiers() const
{
    return modifiers_;
}
inline const Token &ClassStmt::name() const { return name_; }

#endif