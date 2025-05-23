

// Own
#include <ATSPrinter.hpp>
#include <expressions/BinaryExpr.hpp>
#include <expressions/CallExpr.hpp>
#include <expressions/Expr.hpp>
#include <expressions/GroupingExpr.hpp>
#include <expressions/LiteralExpr.hpp>
#include <expressions/LogicalExpr.hpp>
#include <expressions/UnaryExpr.hpp>

std::string ATSPrinter::print(Expr *expr)
{
    return expr->accept(*this);
}

std::string ATSPrinter::visitBinaryExpr(const BinaryExpr &expr)
{
    return parenthesize(expr.op().lexeme(), {expr.left().get(), expr.right().get()});
}

std::string ATSPrinter::visitCallExpr(const CallExpr &expr)
{
    std::string result = "[call " + expr.callee()->accept(*this);

    for (const auto &arg : expr.arguments())
    {
        result += " " + arg->accept(*this);
    }

    result += "]";
    return result;
}

std::string ATSPrinter::visitGroupingExpr(const GroupingExpr &expr)
{
    return parenthesize("group", {expr.expression().get()});
}

std::string ATSPrinter::visitLiteralExpr(const LiteralExpr &expr)
{
    return expr.value().toString();
}

std::string ATSPrinter::visitLogicalExpr(const LogicalExpr &expr)
{
    std::string result = "[logical ";
    result += expr.left()->accept(*this);
    result += " " + expr.op().lexeme() + " ";
    result += expr.right()->accept(*this);
    result += "]";
    return result;
}

std::string ATSPrinter::visitUnaryExpr(const UnaryExpr &expr)
{
    return parenthesize(expr.op().lexeme(), {expr.right().get()});
}

std::string ATSPrinter::parenthesize(const std::string &name, const std::vector<Expr *> &exprs)
{
    std::string result = "(" + name;
    for (Expr *e : exprs)
    {
        result += " " + e->accept(*this);
    }
    result += ")";
    return result;
}