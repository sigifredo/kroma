

// Own
#include <ATSPrinter.hpp>
#include <BinaryExpr.hpp>
#include <Expr.hpp>
#include <GroupingExpr.hpp>
#include <LiteralExpr.hpp>
#include <UnaryExpr.hpp>

std::string ATSPrinter::print(Expr *expr)
{
    return expr->accept(*this);
}

std::string ATSPrinter::visitBinaryExpr(const BinaryExpr &expr)
{
    return parenthesize(expr.op().lexeme(), {expr.left().get(), expr.right().get()});
}

std::string ATSPrinter::visitGroupingExpr(const GroupingExpr &expr)
{
    return parenthesize("group", {expr.expression().get()});
}

std::string ATSPrinter::visitLiteralExpr(const LiteralExpr &expr)
{
    return expr.value().toString();
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