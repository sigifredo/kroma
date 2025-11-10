/**
 * @file Expr.hpp
 * @brief Clase base abstracta para todas las expresiones del AST de Kroma.
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

#ifndef EXPRESSIONS_EXPR_HPP
#define EXPRESSIONS_EXPR_HPP

// own
#include <expressions/ExprVisitor.hpp>
#include <InterpreterVisitor.hpp>
#include <Token.hpp>
#include <Value.hpp>

// std
#include <memory>

/**
 * @class Expr
 * @brief Clase base abstracta del Árbol de Sintaxis Abstracta (AST) para expresiones.
 *
 * Todas las expresiones del lenguaje Kroma derivan de `Expr` e implementan
 * el patrón *Visitor* para:
 * - Generar representaciones textuales del AST (`ExprVisitor`).
 * - Ser evaluadas por el intérprete (`InterpreterVisitor`).
 *
 * @see ExprVisitor
 * @see InterpreterVisitor
 * @see Value
 */
class Expr
{
public:
    /// Destructor virtual para permitir destrucción polimórfica.
    virtual ~Expr() = default;

    /**
     * @brief Acepta un visitante que produce una representación textual del AST.
     *
     * @param visitor Visitante de tipo `ExprVisitor`.
     *
     * @return Cadena con la representación textual de la expresión.
     *
     */
    virtual std::string accept(const ExprVisitor &visitor) const = 0;

    /**
     * @brief Acepta un visitante intérprete que evalúa la expresión.
     *
     * @param visitor Visitante de tipo `InterpreterVisitor`.
     *
     * @return `Value` resultante de la evaluación.
     *
     */
    virtual Value accept(InterpreterVisitor &visitor) const = 0;

    // Futuras extensiones (si se desea exponer API directa):
    // virtual Value evaluate() const = 0;
    // virtual std::string toString() const = 0;
};

#endif
