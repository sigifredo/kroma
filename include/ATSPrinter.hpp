

#ifndef ATSPRINTER_HPP
#define ATSPRINTER_HPP

// Own
#include <ExprVisitor.hpp>

// std
#include <vector>

class Expr;

/**
 * Abstract Syntax Tree Printer
 */
class ATSPrinter : public ExprVisitor
{
public:
    ATSPrinter() = default;

    std::string print(Expr *expr);
    std::string visitAssignExpr(const AssignExpr &expr) override;
    std::string visitBinaryExpr(const BinaryExpr &expr) override;
    std::string visitCallExpr(const CallExpr &expr) override;
    std::string visitGetExpr(const GetExpr &expr) override;
    std::string visitGroupingExpr(const GroupingExpr &expr) override;
    std::string visitLiteralExpr(const LiteralExpr &expr) override;
    std::string visitLogicalExpr(const LogicalExpr &expr) override;
    std::string visitUnaryExpr(const UnaryExpr &expr) override;
    std::string visitVariableExpr(const VariableExpr &expr) override;
};

#endif