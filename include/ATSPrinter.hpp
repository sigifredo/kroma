

#ifndef ATSPRINTER_HPP
#define ATSPRINTER_HPP

// Own
#include <ExprVisitor.hpp>

// std
#include <vector>

class BinaryExpr;
class Expr;
class GroupingExpr;
class LiteralExpr;
class UnaryExpr;

/**
 * Abstract Syntax Tree Printer
 */
class ATSPrinter : public ExprVisitor
{
public:
    ATSPrinter() = default;

    std::string print(Expr *expr);
    std::string visitBinaryExpr(const BinaryExpr &expr) override;
    std::string visitGroupingExpr(const GroupingExpr &expr) override;
    std::string visitLiteralExpr(const LiteralExpr &expr) override;
    std::string visitUnaryExpr(const UnaryExpr &expr) override;

private:
    std::string parenthesize(const std::string &name, const std::vector<Expr *> &exprs);
};

#endif