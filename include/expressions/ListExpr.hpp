

#ifndef EXPRESSIONS_LISTEXPR_HPP
#define EXPRESSIONS_LISTEXPR_HPP

// own
#include <expressions/Expr.hpp>

// std
#include <memory>
#include <vector>

class ListExpr : public Expr
{
public:
    explicit ListExpr(std::vector<std::unique_ptr<Expr>> elements)
        : elements_(std::move(elements)) {}

    std::string accept(const ExprVisitor &visitor) const override;
    Value accept(InterpreterVisitor &visitor) const override;

    const std::vector<std::unique_ptr<Expr>> &elements() const;

private:
    std::vector<std::unique_ptr<Expr>> elements_;
};

inline std::string ListExpr::accept(const ExprVisitor &visitor) const { return visitor.visitListExpr(*this); }
inline Value ListExpr::accept(InterpreterVisitor &visitor) const { return visitor.visitListExpr(*this); }
inline const std::vector<std::unique_ptr<Expr>> &ListExpr::elements() const { return elements_; }

#endif
