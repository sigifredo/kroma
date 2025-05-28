

// Own
#include <ATSPrinter.hpp>
#include <expressions/AssignExpr.hpp>
#include <expressions/BinaryExpr.hpp>
#include <expressions/CallExpr.hpp>
#include <expressions/Expr.hpp>
#include <expressions/GetExpr.hpp>
#include <expressions/GroupingExpr.hpp>
#include <expressions/LiteralExpr.hpp>
#include <expressions/LogicalExpr.hpp>
#include <expressions/UnaryExpr.hpp>
#include <expressions/VariableExpr.hpp>

std::string ATSPrinter::print(Expr *expr)
{
    return expr->accept(*this);
}

std::string ATSPrinter::visitAssignExpr(const AssignExpr &expr) const
{
    std::string result = "[assign ";
    result += expr.name().lexeme() + " = ";
    result += expr.value()->accept(*this);
    result += "]";
    return result;
}

std::string ATSPrinter::visitBinaryExpr(const BinaryExpr &expr) const
{
    return "[binary " + expr.left()->accept(*this) + " " + expr.op().lexeme() + " " + expr.right()->accept(*this) + "]";
}

std::string ATSPrinter::visitCallExpr(const CallExpr &expr) const
{
    std::string result = "[call " + expr.callee()->accept(*this);

    for (const auto &arg : expr.arguments())
    {
        result += " " + arg->accept(*this);
    }

    result += "]";
    return result;
}

std::string ATSPrinter::visitGetExpr(const GetExpr &expr) const
{
    return "[get " + expr.object()->accept(*this) + "." + expr.name().lexeme() + "]";
}

std::string ATSPrinter::visitGroupingExpr(const GroupingExpr &expr) const
{
    return "[group " + expr.expression()->accept(*this) + "]";
}

std::string ATSPrinter::visitLiteralExpr(const LiteralExpr &expr) const
{
    return "[literal " + expr.value().toString() + "]";
}

std::string ATSPrinter::visitLogicalExpr(const LogicalExpr &expr) const
{
    std::string result = "[logical ";
    result += expr.left()->accept(*this);
    result += " " + expr.op().lexeme() + " ";
    result += expr.right()->accept(*this);
    result += "]";
    return result;
}

std::string ATSPrinter::visitUnaryExpr(const UnaryExpr &expr) const
{
    return "[unary " + expr.op().lexeme() + " " + expr.right()->accept(*this) + "]";
}

std::string ATSPrinter::visitVariableExpr(const VariableExpr &expr) const
{
    return expr.name().lexeme();
}
