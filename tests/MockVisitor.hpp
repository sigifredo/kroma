

#ifndef TEST_MOCKVISITOR_HPP
#define TEST_MOCKVISITOR_HPP

// own
#include <expressions/ExprVisitor.hpp>

class MockVisitor : public ExprVisitor
{
public:
    std::string visitRangeExpr(const RangeExpr &expr) const override
    {
        return "VisitedRange";
    }
};

#endif