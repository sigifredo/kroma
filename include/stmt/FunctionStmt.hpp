

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
                 std::vector<std::unique_ptr<VarStmt>> params,
                 std::vector<std::unique_ptr<Stmt>> body,
                 std::vector<Token> modifiers = {},
                 isOperator = false)
        : name_(name),
          body_(std::move(body)),
          params_(std::move(params)),
          modifiers_(std::move(modifiers)),
          isOperator_(isOperator) {}

    std::string accept(StmtVisitor &visitor) const override;
    void accept(InterpreterVisitor &) const override {}

    auto body() const;
    bool isOperator() const;
    auto modifiers() const;
    const Token &name() const;
    auto params() const;

private:
    std::vector<std::unique_ptr<Stmt>> body_;
    bool isOperator_;
    std::vector<std::unique_ptr<VarStmt>> params_;
    std::vector<Token> modifiers_;
    Token name_;
};

inline std::string FunctionStmt::accept(StmtVisitor &visitor) const { return visitor.visitFunctionStmt(*this); }
inline auto FunctionStmt::body() const
{
    return body_ | std::views::transform([](const unique_ptr<Stmt> &arg)
                                         { return arg.get(); });
}
inline bool FunctionStmt::isOperator() const { return isOperator_; }
inline const std::vector<Token> &FunctionStmt::modifiers() const { return modifiers_; }
const Token &FunctionStmt::name() const { return name_; }
inline auto FunctionStmt::params() const
{
    return params_ | std::views::transform([](const unique_ptr<VarStmt> &arg)
                                           { return arg.get(); });
}

#endif