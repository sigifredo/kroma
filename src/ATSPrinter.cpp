

// own
#include <ATSPrinter.hpp>
#include <expressions/AssignExpr.hpp>
#include <expressions/BinaryExpr.hpp>
#include <expressions/CallExpr.hpp>
#include <expressions/Expr.hpp>
#include <expressions/FStringExpr.hpp>
#include <expressions/GetExpr.hpp>
#include <expressions/GroupingExpr.hpp>
#include <expressions/IndexExpr.hpp>
#include <expressions/ListExpr.hpp>
#include <expressions/LiteralExpr.hpp>
#include <expressions/LogicalExpr.hpp>
#include <expressions/RangeExpr.hpp>
#include <expressions/UnaryExpr.hpp>
#include <expressions/VariableExpr.hpp>
#include <stmt/ExpressionStmt.hpp>
#include <stmt/Stmt.hpp>
#include <stmt/VarStmt.hpp>

// std
#include <sstream>

std::string ATSPrinter::print(const Expr *expr) const
{
    return expr->accept(*this);
}

std::string ATSPrinter::print(const Stmt *stmt)
{
    return stmt->accept(*this);
}

std::string ATSPrinter::visit(const AssignExpr &expr) const
{
    std::string result = "[assign ";
    result += expr.name().lexeme() + " = ";
    result += expr.value()->accept(*this);
    result += "]";
    return result;
}

std::string ATSPrinter::visit(const BinaryExpr &expr) const
{
    return "[binary " + expr.left()->accept(*this) + " " + expr.op().lexeme() + " " + expr.right()->accept(*this) + "]";
}

std::string ATSPrinter::visit(const CallExpr &expr) const
{
    std::string result = "[call " + expr.callee()->accept(*this);

    for (const auto &arg : expr.arguments())
    {
        result += " " + arg->accept(*this);
    }

    result += "]";
    return result;
}

std::string ATSPrinter::visit(const FStringExpr &expr) const
{
    std::string result = "f\"";

    for (const auto &part : expr.parts())
    {
        if (auto literal = dynamic_cast<const LiteralExpr *>(part.get()))
            result += literal->value().toString();
        else
            result += "{" + part->accept(*this) + "}";
    }

    result += "\"";
    return result;
}

std::string ATSPrinter::visit(const GetExpr &expr) const
{
    return "[get " + expr.object()->accept(*this) + "." + expr.name().lexeme() + "]";
}

std::string ATSPrinter::visit(const GroupingExpr &expr) const
{
    return "[group " + expr.expression()->accept(*this) + "]";
}

std::string ATSPrinter::visit(const IndexExpr &expr) const
{
    return std::string("(index " + expr.target()->accept(*this) + " " + expr.index()->accept(*this) + ")");
}

std::string ATSPrinter::visit(const ListExpr &expr) const
{
    std::string result("[list");

    for (const auto &element : expr.elements())
    {
        if (auto list = dynamic_cast<const LiteralExpr *>(element.get()))
            result += " " + list->value().toString();
    }

    return result;
}

std::string ATSPrinter::visit(const LiteralExpr &expr) const
{
    return "[literal " + expr.value().toString() + "]";
}

std::string ATSPrinter::visit(const LogicalExpr &expr) const
{
    std::string result = "[logical ";
    result += expr.left()->accept(*this);
    result += " " + expr.op().lexeme() + " ";
    result += expr.right()->accept(*this);
    result += "]";
    return result;
}

std::string ATSPrinter::visit(const RangeExpr &expr) const
{
    std::string result = "(range ";

    result += expr.start() ? expr.start()->accept(*this) : "null";
    result += " .. ";
    result += expr.end() ? expr.end()->accept(*this) : "null";

    if (expr.step())
    {
        result += " by ";
        result += expr.step()->accept(*this);
    }

    result += ")";
    return result;
}

std::string ATSPrinter::visit(const UnaryExpr &expr) const
{
    return "[unary " + expr.op().lexeme() + " " + expr.right()->accept(*this) + "]";
}

std::string ATSPrinter::visit(const VariableExpr &expr) const
{
    return expr.name().lexeme();
}

std::string ATSPrinter::visitBlockStmt(const BlockStmt &stmt) const
{
    return std::string("[unimplemented] ") + std::string(__func__) + ":" + std::to_string(__LINE__) + " -> " + __FILE__;
}

std::string ATSPrinter::visitClassStmt(const ClassStmt &stmt)
{
    return std::string("[unimplemented] ") + std::string(__func__) + ":" + std::to_string(__LINE__) + " -> " + __FILE__;
}

std::string ATSPrinter::visitExpressionStmt(const ExpressionStmt &stmt) const
{
    return "(expr " + print(stmt.expression()) + ")";
}

std::string ATSPrinter::visitForEachStmt(const ForEachStmt &stmt)
{
    return std::string("[unimplemented] ") + std::string(__func__) + ":" + std::to_string(__LINE__) + " -> " + __FILE__;
}

std::string ATSPrinter::visitForRangeStmt(const ForRangeStmt &stmt)
{
    return std::string("[unimplemented] ") + std::string(__func__) + ":" + std::to_string(__LINE__) + " -> " + __FILE__;
}

std::string ATSPrinter::visitFunctionStmt(const FunctionStmt &stmt)
{
    return std::string("[unimplemented] ") + std::string(__func__) + ":" + std::to_string(__LINE__) + " -> " + __FILE__;
}

std::string ATSPrinter::visitIfStmt(const IfStmt &stmt) const
{
    return std::string("[unimplemented] ") + std::string(__func__) + ":" + std::to_string(__LINE__) + " -> " + __FILE__;
}

std::string ATSPrinter::visitPrintStmt(const PrintStmt &stmt) const
{
    return std::string("[unimplemented] ") + std::string(__func__) + ":" + std::to_string(__LINE__) + " -> " + __FILE__;
}

std::string ATSPrinter::visitReturnStmt(const ReturnStmt &stmt) const
{
    return std::string("[unimplemented] ") + std::string(__func__) + ":" + std::to_string(__LINE__) + " -> " + __FILE__;
}

std::string ATSPrinter::visitVarStmt(const VarStmt &stmt) const
{
    std::ostringstream out;

    out << "(";
    out << stmt.modifier().lexeme() << " ";
    out << stmt.name().lexeme();

    if (stmt.initializer())
    {
        out << " = " << stmt.initializer()->accept(*this);
    }

    out << ")";
    return out.str();
}