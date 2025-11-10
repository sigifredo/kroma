/**
 * @file GroupingExpr.hpp
 * @brief Declaración de la clase GroupingExpr, que representa una agrupación de expresiones en Kroma.
 * @license MIT
 *
 * @copyright
 * Copyright (c) 2025 Sigifredo Escobar Gómez
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef EXPRESSIONS_GROUPINGEXPR_HPP
#define EXPRESSIONS_GROUPINGEXPR_HPP

// own
#include <expressions/Expr.hpp>

/**
 * @class GroupingExpr
 * @brief Clase que representa una expresión agrupada (entre paréntesis) en el AST de Kroma.
 *
 * La clase **GroupingExpr** encapsula otra expresión dentro de paréntesis,
 * preservando su precedencia y asegurando que se evalúe como una unidad lógica.
 *
 * ### Ejemplo en código Kroma:
 * @code
 * let resultado = (a + b) * 2
 * @endcode
 *
 * En este caso, la expresión `(a + b)` se modela como un nodo `GroupingExpr`.
 *
 * @see Expr
 * @see InterpreterVisitor
 * @see Token
 */
class GroupingExpr : public Expr
{
public:
    /**
     * @brief Constructor de GroupingExpr.
     *
     * @param expr Puntero a la expresión contenida dentro del agrupamiento.
     *
     */
    explicit GroupingExpr(std::unique_ptr<Expr> expr)
        : expression_(std::move(expr)) {}

    /**
     * @brief Acepta un visitante que genera una representación textual del AST.
     *
     * @param visitor Visitante de tipo ExprVisitor.
     *
     * @return Representación textual de la expresión agrupada.
     *
     */
    std::string accept(const ExprVisitor &visitor) const override;

    /**
     * @brief Acepta un visitante intérprete que evalúa la expresión agrupada.
     *
     * @param visitor Visitante de tipo InterpreterVisitor.
     *
     * @return Valor resultante de la evaluación.
     *
     */
    Value accept(InterpreterVisitor &visitor) const override;

    /**
     * @brief Devuelve la expresión contenida dentro del agrupamiento.
     *
     * @return Puntero constante a la expresión interna.
     *
     */
    const Expr *expression() const;

private:
    std::unique_ptr<Expr> expression_; ///< Expresión contenida dentro de los paréntesis.
};

// Implementaciones inline

inline std::string GroupingExpr::accept(const ExprVisitor &visitor) const { return visitor.visit(*this); }
#warning "Implementar método GroupingExpr::accept(InterpreterVisitor &) correctamente"
inline Value GroupingExpr::accept(InterpreterVisitor &visitor) const { return Value("visitor.visitGroupingExpr(*this)"); }
inline const Expr *GroupingExpr::expression() const { return expression_.get(); }

#endif