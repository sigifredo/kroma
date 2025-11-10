/**
 * @file BinaryExpr.hpp
 * @brief Declaración de la clase BinaryExpr, que representa una expresión binaria en el AST de Kroma.
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

/**
 * @class BinaryExpr
 * @brief Clase que representa una expresión binaria en el sistema de expresiones del intérprete de Kroma.
 *
 * La clase **BinaryExpr** modela una operación binaria entre dos expresiones,
 * como suma, resta, multiplicación, comparación o concatenación.
 * Forma parte del Árbol de Sintaxis Abstracta (AST) que el intérprete de Kroma
 * utiliza para evaluar expresiones aritméticas y lógicas.
 *
 * ### Ejemplo en código Kroma:
 * @code
 * let resultado = (a + b) * 2
 * @endcode
 *
 * En este caso, el nodo raíz del AST es una instancia de `BinaryExpr` que
 * representa la multiplicación, y sus nodos hijos son también expresiones binarias o literales.
 *
 * @see Expr
 * @see InterpreterVisitor
 * @see Token
 */

#ifndef EXPRESSIONS_BINARYEXPR_HPP
#define EXPRESSIONS_BINARYEXPR_HPP

// own
#include <expressions/Expr.hpp>

/**
 * @brief Nodo del AST que representa una operación binaria.
 *
 * Un `BinaryExpr` contiene dos operandos (izquierdo y derecho) y un operador.
 * Los operadores pueden representar operaciones aritméticas (`+`, `-`, `*`, `/`),
 * comparativas (`==`, `!=`, `<`, `>`), o lógicas (`and`, `or`).
 */
class BinaryExpr : public Expr
{
public:
    /**
     * @brief Constructor de BinaryExpr.
     *
     * @param leftExpr Expresión izquierda del operador.
     * @param oper Token que representa el operador.
     * @param rightExpr Expresión derecha del operador.
     *
     */
    BinaryExpr(std::unique_ptr<Expr> leftExpr,
               const Token &oper,
               std::unique_ptr<Expr> rightExpr)
        : left_(std::move(leftExpr)),
          op_(oper),
          right_(std::move(rightExpr)) {};

    /**
     * @brief Acepta un visitante que genera una representación textual del AST.
     *
     * @param visitor Visitante de tipo ExprVisitor.
     *
     * @return Representación textual de la expresión binaria.
     *
     */
    std::string accept(const ExprVisitor &visitor) const override;

    /**
     * @brief Acepta un visitante intérprete que evalúa la expresión.
     *
     * @param visitor Visitante de tipo InterpreterVisitor.
     *
     * @return Valor resultante de la evaluación.
     *
     */
    Value accept(InterpreterVisitor &visitor) const override;

    /**
     * @brief Devuelve la expresión izquierda.
     *
     * @return Puntero constante a la expresión izquierda.
     *
     */
    const Expr *left() const;

    /**
     * @brief Devuelve el token que representa el operador.
     *
     * @return Referencia constante al token del operador.
     *
     */
    const Token &op() const;

    /**
     * @brief Devuelve la expresión derecha.
     *
     * @return Puntero constante a la expresión derecha.
     *
     */
    const Expr *right() const;

private:
    std::unique_ptr<Expr> left_;  ///< Expresión izquierda del operador.
    Token op_;                    ///< Token que representa el operador.
    std::unique_ptr<Expr> right_; ///< Expresión derecha del operador.
};

// Implementaciones inline

inline std::string BinaryExpr::accept(const ExprVisitor &visitor) const { return visitor.visit(*this); }
inline Value BinaryExpr::accept(InterpreterVisitor &visitor) const { return visitor.visitBinaryExpr(*this); }
inline const Expr *BinaryExpr::left() const { return left_.get(); }
inline const Token &BinaryExpr::op() const { return op_; }
inline const Expr *BinaryExpr::right() const { return right_.get(); }

#endif
