
// own
#include <Interpreter.hpp>
#include <Utils.hpp>

// own errors
#include <errors/RuntimeError.hpp>
#include <errors/ValueError.hpp>

// Expressions
#include <expressions/AssignExpr.hpp>
#include <expressions/BinaryExpr.hpp>
#include <expressions/Expr.hpp>
#include <expressions/FStringExpr.hpp>
#include <expressions/ListExpr.hpp>
#include <expressions/LogicalExpr.hpp>
#include <expressions/RangeExpr.hpp>
#include <expressions/UnaryExpr.hpp>
#include <expressions/VariableExpr.hpp>

// Stmts
#include <stmt/BlockStmt.hpp>
#include <stmt/ExpressionStmt.hpp>
#include <stmt/IfStmt.hpp>
#include <stmt/PrintStmt.hpp>
#include <stmt/VarStmt.hpp>

// std
#include <cmath>

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

Value Interpreter::visitFStringExpr(const FStringExpr &expr)
{
    std::string result;

    for (const auto &part : expr.parts())
    {
        result += evaluate(*part).toString();
    }

    return Value(result);
}

Value Interpreter::visitListExpr(const ListExpr &expr)
{
    std::vector<Value> lst;

    for (const auto &exp : expr.elements())
    {
        lst.emplace_back(evaluate(*exp));
    }

    return Value{std::move(lst)};
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

Value Interpreter::visitRangeExpr(const RangeExpr &expr)
{
    auto stepExpr = expr.step();
    Value startValue = evaluate(*expr.start());
    Value endValue = evaluate(*expr.end());
    Value stepValue = (stepExpr == nullptr) ? Value(1) : evaluate(*stepExpr);

    auto isAlmostInt = [&](double x)
    {
        double r = std::round(x);
        return std::abs(x - r) <= 1e-9 * std::max(1.0, std::abs(x));
    };
    auto asNumberChecked = [](const Value &v, const char *what) -> double
    {
        if (!v.isNumber())
            throw ValueError(std::string("Rango inválido: ") + what + " debe ser un número. Recibido: " + v.toString());
        double d = v.asNumber();
        if (!std::isfinite(d))
            throw ValueError(std::string("Rango inválido: ") + what + " no puede ser NaN/Inf. Recibido: " + v.toString());
        return d;
    };

    const double start = asNumberChecked(startValue, "el inicio");
    const double end = asNumberChecked(endValue, "el fin");
    const double step = asNumberChecked(stepValue, "el paso");

    if (step == 0.0)
        throw ValueError("Rango inválido: el paso no puede ser cero.");

    const int dir = (end > start) ? 1 : (end < start ? -1 : 0);
    const int sgn = (step > 0.0) ? 1 : -1;

    if (dir == 0)
    {
        std::vector<Value> out;

        if (isAlmostInt(start))
            out.emplace_back(static_cast<int64_t>(std::llround(start)));
        else
            out.emplace_back(start);

        return Value{std::move(out)};
    }

    if (sgn != dir)
    {
        throw ValueError(
            "Rango inválido: el paso debe apuntar hacia el fin. "
            "Use paso positivo para rangos ascendentes y negativo para descendentes. "
            "inicio=" +
            std::to_string(start) + ", fin=" + std::to_string(end) + ", paso=" + std::to_string(step));
    }

    if (start + step == start)
        throw ValueError("Rango inválido: el paso es demasiado pequeño para el tipo numérico (no produce avance).");

    const double absStep = std::abs(step);
    const double eps = std::max(1e-12, absStep * 1e-12);
    std::size_t reserveN = 0;

    if (std::isfinite(start) && std::isfinite(end) && std::isfinite(step))
    {
        const double span = std::abs(end - start);

        if (absStep > 0.0 && std::isfinite(span))
        {
            double n = std::floor((span + eps) / absStep) + 1.0;

            if (n > 0.0 && n < 5e7)
                reserveN = static_cast<std::size_t>(n);
            else if (n >= 5e7)
            {
                throw ValueError("Rango demasiado grande: tamaño estimado " + std::to_string(static_cast<long double>(n)));
            }
        }
    }

    std::vector<Value> out;

    if (reserveN)
        out.reserve(reserveN);

    const bool wantInts = isAlmostInt(start) && isAlmostInt(end) && isAlmostInt(step);

    if (dir > 0)
    {
        for (double x = start; x <= end + eps; x += step)
        {
            if (wantInts)
                out.emplace_back(static_cast<int64_t>(std::llround(x)));
            else
                out.emplace_back(x);
        }
    }
    else
    {
        for (double x = start; x >= end - eps; x += step)
        {
            if (wantInts)
                out.emplace_back(static_cast<int64_t>(std::llround(x)));
            else
                out.emplace_back(x);
        }
    }

    return Value{std::move(out)};
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