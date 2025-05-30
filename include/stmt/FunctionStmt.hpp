

#ifndef STMT_FUNCTIONSTMT_HPP
#define STMT_FUNCTIONSTMT_HPP

// own
#include <stmt/VarStmt.hpp>
#include <Token.hpp>

// std
#include <memory>

class FunctionStmt : public Stmt
{
public:
    FunctionStmt(const Token &name,
                 std::vector<unique_ptr<VarStmt>> params,
                 std::vector<unique_ptr<Stmt>> body,
                 std::vector<Token> modifiers = {},
                 isOperator = false)
        : name_(name),
          body_(std::move(body)),
          params_(std::move(params)),
          modifiers_(std::move(modifiers)),
          isOperator_(isOperator) {}

    void accept(StmtVisitor &visitor) const override;

    // TODO: corregir métodos acessores
    const Token &name() const;
    auto body() const;
    auto params() const;
    const std::vector<Token> &modifiers() const;
    bool isOperator() const;

private:
    Token name_;
    std::vector<unique_ptr<Stmt>> body_;
    std::vector<unique_ptr<VarStmt>> params_;
    std::vector<Token> modifiers_;
    bool isOperator_;
};

// TODO: Organizar métodos inline
inline void FunctionStmt::accept(StmtVisitor &visitor) const { visitor.visitFunctionStmt(*this); }
inline auto FunctionStmt::params() const
{
    return params_ | std::views::transform([](const unique_ptr<VarStmt> &arg)
                                           { return arg.get(); });
}
const Token &FunctionStmt::name() const { return name_; }
auto FunctionStmt::body() const
{
    return body_ | std::views::transform([](const unique_ptr<Stmt> &arg)
                                         { return arg.get(); });
}
const std::vector<Token> &FunctionStmt::modifiers() const { return modifiers_; }
bool FunctionStmt::isOperator() const { return isOperator_; }

#endif