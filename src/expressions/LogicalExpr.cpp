

// Own
#include <expressions/LogicalExpr.hpp>
#include <ExprVisitor.hpp>

std::string LogicalExpr::accept(ExprVisitor &visitor)
{
    return visitor.visitLogicalExpr(*this);
}