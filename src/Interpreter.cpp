
// own
#include <Interpreter.hpp>
#include <RuntimeError.hpp>
#include <Utils.hpp>

// Expressions
#include <expressions/AssignExpr.hpp>
#include <expressions/BinaryExpr.hpp>
#include <expressions/Expr.hpp>
#include <expressions/LogicalExpr.hpp>
#include <expressions/UnaryExpr.hpp>
#include <expressions/VariableExpr.hpp>

// Stmts
#include <stmt/BlockStmt.hpp>
#include <stmt/ExpressionStmt.hpp>
#include <stmt/IfStmt.hpp>
#include <stmt/PrintStmt.hpp>
#include <stmt/VarStmt.hpp>

void Interpreter::interpret(const std::vector<std::unique_ptr<Stmt>> &statements)
{
    for (const auto &stmt : statements)
    {
        try
        {
            stmt->accept(*this);
        }
        catch (const RuntimeError &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}

void Interpreter::printVariables() const
{
    environment_->debugPrint();
}

Value Interpreter::visitAssignExpr(const AssignExpr &expr)
{
    Value value = evaluate(*expr.value());
    environment_->assign(expr.name().lexeme(), value);

    return value;
}

Value Interpreter::visitBinaryExpr(const BinaryExpr &expr)
{
    Value left = evaluate(*expr.left());
    Value right = evaluate(*expr.right());

    switch (expr.op().type())
    {
    case TokenType::PLUS:
    {
        auto visitor = overloaded{
            [](double a, double b)
            { return Value(a + b); },
            [](const std::string &a, const std::string &b)
            { return Value(a + b); },
            [](auto &&, auto &&) -> Value
            {
                throw RuntimeError("Tipos incompatibles");
            }};

        return Value::visit(std::ref(visitor), left, right);
    }
    case TokenType::MINUS:
        return binaryNumericOp(left, right, std::minus{});

    case TokenType::STAR:
        return binaryNumericOp(left, right, std::multiplies{});

    case TokenType::SLASH:
        return binaryNumericOp(
            left,
            right,
            [](double a, double b)
            {
                if (b == 0) throw RuntimeError("Division by zero.");
                return a / b; });
    default:
        throw RuntimeError("Unknown binary operator.");
    }
}

Value Interpreter::visitLogicalExpr(const LogicalExpr &expr)
{
    Value left = evaluate(*expr.left());

    if (expr.op().type() == TokenType::OR)
    {
        if (left.asBool())
            return left;
    }
    else if (expr.op().type() == TokenType::AND)
    {
        if (!left.asBool())
            return left;
    }
    else
    {
        throw RuntimeError("Operador lógico desconocido");
    }

    return evaluate(*expr.right());
}

Value Interpreter::visitUnaryExpr(const UnaryExpr &expr)
{
    Value right = evaluate(*expr.right());

    switch (expr.op().type())
    {
    case TokenType::MINUS:
        if (!right.isNumber())
            throw RuntimeError("El operando debe ser un número");
        return Value(-right.asNumber());

    case TokenType::BANG:
        return Value(!right.asBool());

    default:
        throw RuntimeError("Operador unario desconocido.");
    }
}

Value Interpreter::visitVariableExpr(const VariableExpr &expr)
{
    return environment_->get(expr.name().lexeme());
}

void Interpreter::visitBlockStmt(const BlockStmt &stmt)
{
    std::shared_ptr<Environment> newEnv = std::make_shared<Environment>(environment_);
    executeBlock(stmt.statements(), newEnv);
}

void Interpreter::visitExpressionStmt(const ExpressionStmt &stmt)
{
    evaluate(*stmt.expression());
}

void Interpreter::visitIfStmt(const IfStmt &stmt)
{
    Value condition = evaluate(*stmt.condition());

    if (isTrue(condition))
        execute(*stmt.thenBranch());
    else if (stmt.elseBranch())
        execute(*stmt.elseBranch());
}

void Interpreter::visitPrintStmt(const PrintStmt &stmt)
{
    std::cout << evaluate(*stmt.expression()) << std::endl;
}

void Interpreter::visitVarStmt(const VarStmt &stmt)
{
    Value value;

    if (stmt.initializer())
    {
        value = evaluate(*stmt.initializer());
    }
    else
    {
        value = Value{};
    }

    environment_->define(stmt.name().lexeme(), value, stmt.modifier().type() == TokenType::CONST);
}

Value Interpreter::evaluate(const Expr &expr)
{
    return expr.accept(*this);
}

void Interpreter::execute(const Stmt &stmt)
{
    stmt.accept(*this);
}

void Interpreter::executeBlock(const std::vector<std::unique_ptr<Stmt>> &statements, std::shared_ptr<Environment> newEnv)
{
    std::shared_ptr<Environment> previous = environment_;
    environment_ = newEnv;

    try
    {
        for (const auto &stmt : statements)
        {
            execute(*stmt);
        }
    }
    catch (...)
    {
        environment_ = previous;
        throw;
    }

    environment_ = previous;
}

bool Interpreter::isTrue(const Value &value)
{
    if (value.isNull())
        return false;

    if (value.isBool())
        return value.asBool();

    return true;
}