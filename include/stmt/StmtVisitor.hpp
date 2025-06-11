

#ifndef STMT_STMTVISITOR_HPP
#define STMT_STMTVISITOR_HPP

class BlockStmt;
class ClassStmt;
class ExpressionStmt;
class ForEachStmt;
class ForRangeStmt;
class FunctionStmt;
class IfStmt;
class PrintStmt;
class ReturnStmt;
class VarStmt;

class StmtVisitor
{
public:
    StmtVisitor() = default;
    virtual ~StmtVisitor() = default;

    virtual std::string visitBlockStmt(const BlockStmt &stmt) = 0;
    virtual std::string visitClassStmt(const ClassStmt &stmt) = 0;
    virtual std::string visitExpressionStmt(const ExpressionStmt &stmt) const = 0;
    virtual std::string visitForEachStmt(const ForEachStmt &stmt) = 0;
    virtual std::string visitForRangeStmt(const ForRangeStmt &stmt) = 0;
    virtual std::string visitFunctionStmt(const FunctionStmt &stmt) = 0;
    virtual std::string visitIfStmt(const IfStmt &stmt) const = 0;
    virtual std::string visitPrintStmt(const PrintStmt &stmt) const = 0;
    virtual std::string visitReturnStmt(const ReturnStmt &stmt) const = 0;
    virtual std::string visitVarStmt(const VarStmt &stmt) const = 0;
};

#endif