

#ifndef ATSPRINTER_HPP
#define ATSPRINTER_HPP

// own
#include <expressions/ExprVisitor.hpp>

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
    std::string visitAssignExpr(const AssignExpr &expr) const override;
    std::string visitBinaryExpr(const BinaryExpr &expr) const override;
    std::string visitCallExpr(const CallExpr &expr) const override;
    std::string visitGetExpr(const GetExpr &expr) const override;
    std::string visitGroupingExpr(const GroupingExpr &expr) const override;
    std::string visitLiteralExpr(const LiteralExpr &expr) const override;
    std::string visitLogicalExpr(const LogicalExpr &expr) const override;
    std::string visitRangeExpr(const RangeExpr &expr) const override;
    std::string visitUnaryExpr(const UnaryExpr &expr) const override;
    std::string visitVariableExpr(const VariableExpr &expr) const override;
};

#endif