/**
 * @file AssignExpr.hpp
 * @brief Declaración de la clase AssignExpr, que representa una expresión de asignación en el AST de Kroma.
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
 * @class AssignExpr
 * @brief Clase que representa una expresión de asignación en el sistema de expresiones del intérprete de Kroma.
 *
 * La clase **AssignExpr** modela una operación de asignación de valor a una variable existente.
 * Forma parte del Árbol de Sintaxis Abstracta (AST) del intérprete de Kroma.
 *
 * ### Ejemplo en código Kroma:
 * @code
 * let x = 5
 * x = x + 2
 * @endcode
 *
 * En este caso, la segunda línea se representa internamente como un nodo `AssignExpr`.
 *
 * @see Expr
 * @see InterpreterVisitor
 * @see Token
 */

#ifndef EXPRESSIONS_ASSIGNEXPR_HPP
#define EXPRESSIONS_ASSIGNEXPR_HPP

// own
#include <expressions/Expr.hpp>

/**
 * @class AssignExpr
 * @brief Nodo del AST que representa una expresión de asignación.
 *
 * La clase `AssignExpr` se utiliza para asignar un nuevo valor a una variable
 * ya existente en el entorno de ejecución. Contiene un nombre de variable (`Token`)
 * y una expresión cuyo valor será evaluado y asignado a dicha variable.
 */
class AssignExpr : public Expr
{
public:
    /**
     * @brief Constructor de AssignExpr.
     *
     * @param name Token que identifica el nombre de la variable.
     * @param value Puntero único a la expresión cuyo resultado se asignará.
     *
     */
    AssignExpr(const Token &name, std::unique_ptr<Expr> value)
        : name_(name), value_(std::move(value)) {}

    /**
     * @brief Acepta un visitante que genera una representación textual del AST.
     *
     * @param visitor Visitante de tipo ExprVisitor.
     * @return Representación textual del nodo.
     *
     */
    std::string accept(const ExprVisitor &visitor) const override;

    /**
     * @brief Acepta un visitante intérprete que evalúa la asignación.
     *
     * @param visitor Visitante de tipo InterpreterVisitor.
     *
     * @return Valor resultante de la operación de asignación.
     */
    Value accept(InterpreterVisitor &visitor) const override;

    /**
     * @brief Devuelve el token asociado al nombre de la variable.
     *
     * @return Referencia constante al token.
     *
     */
    const Token &name() const;

    /**
     * @brief Devuelve la expresión que representa el valor asignado.
     *
     * @return Puntero constante a la expresión del valor.
     *
     */
    const Expr *value() const;

private:
    Token name_;                  ///< Token que representa el nombre de la variable.
    std::unique_ptr<Expr> value_; ///< Expresión cuyo valor será asignado.
};

// Implementaciones inline

inline std::string AssignExpr::accept(const ExprVisitor &visitor) const { return visitor.visit(*this); }
inline Value AssignExpr::accept(InterpreterVisitor &visitor) const { return visitor.visitAssignExpr(*this); }
inline const Token &AssignExpr::name() const { return name_; }
inline const Expr *AssignExpr::value() const { return value_.get(); }

#endif
