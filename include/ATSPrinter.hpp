

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
    std::string visitBinaryExpr(const BinaryExpr &expr) override;
    std::string visitCallExpr(const CallExpr &expr) override;
    std::string visitGroupingExpr(const GroupingExpr &expr) override;
    std::string visitLiteralExpr(const LiteralExpr &expr) override;
    std::string visitLogicalExpr(const LogicalExpr &expr) override;
    std::string visitUnaryExpr(const UnaryExpr &expr) override;

private:
    std::string parenthesize(const std::string &name, const std::vector<Expr *> &exprs);
};

#endif