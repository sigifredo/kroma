

#ifndef ATSPRINTER_HPP
#define ATSPRINTER_HPP

// own
#include <expressions/ExprVisitor.hpp>
#include <stmt/StmtVisitor.hpp>

// std
#include <vector>

class Expr;
class Stmt;

/**
 * Abstract Syntax Tree Printer
 */
class ATSPrinter : public ExprVisitor, public StmtVisitor
{
public:
    ATSPrinter() = default;

    std::string print(Expr *expr);
    std::string print(Stmt *stmt);

    // --- ExprVisitor ---
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

    // --- StmtVisitor ---
    std::string visitBlockStmt(const BlockStmt &stmt) override;
    std::string visitClassStmt(const ClassStmt &stmt) override;
    std::string visitExpressionStmt(const ExpressionStmt &stmt) override;
    std::string visitForEachStmt(const ForEachStmt &stmt) override;
    std::string visitForRangeStmt(const ForRangeStmt &stmt) override;
    std::string visitFunctionStmt(const FunctionStmt &stmt) override;
    std::string visitIfStmt(const IfStmt &stmt) override;
    std::string visitReturnStmt(const ReturnStmt &stmt) override;
    std::string visitVarStmt(const VarStmt &stmt) override;
};

#endif