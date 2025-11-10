/**
 * @file FStringExpr.hpp
 * @brief Declaración de la clase FStringExpr, que representa una expresión de interpolación de texto (f-string) en Kroma.
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

#ifndef EXPRESSIONS_FSTRINGEXPR_HPP
#define EXPRESSIONS_FSTRINGEXPR_HPP

// own
#include <expressions/Expr.hpp>

/**
 * @class FStringExpr
 * @brief Clase que representa una f-string (cadena interpolada) dentro del AST de Kroma.
 *
 * La clase **FStringExpr** permite construir cadenas dinámicas que incluyen
 * expresiones evaluables dentro de un literal de texto, similar a las *f-strings* de Python.
 *
 * Cada parte de la interpolación (texto literal o expresión embebida)
 * se almacena como un nodo `Expr` dentro del vector `parts_`.
 *
 * ### Ejemplo en código Kroma:
 * @code
 * let nombre = "Sigi"
 * print(f"Hola {nombre}, bienvenido a Kroma!")
 * @endcode
 *
 * Internamente, esta expresión se representa como un `FStringExpr` con múltiples subexpresiones.
 *
 * @see Expr
 * @see InterpreterVisitor
 * @see Token
 */
class FStringExpr : public Expr
{
public:
    /**
     * @brief Constructor de FStringExpr.
     *
     * @param parts Lista de expresiones que componen la f-string (texto y expresiones).
     *
     */
    explicit FStringExpr(std::vector<std::unique_ptr<Expr>> parts)
        : parts_(std::move(parts)) {}

    /**
     * @brief Acepta un visitante que genera una representación textual del AST.
     *
     * @param visitor Visitante de tipo ExprVisitor.
     *
     * @return Representación textual de la f-string.
     *
     */
    std::string accept(const ExprVisitor &visitor) const override;

    /**
     * @brief Acepta un visitante intérprete que evalúa la f-string.
     *
     * @param visitor Visitante de tipo InterpreterVisitor.
     *
     * @return Valor resultante de la evaluación de la cadena interpolada.
     *
     */
    Value accept(InterpreterVisitor &visitor) const override;

    /**
     * @brief Devuelve la lista de partes que componen la f-string.
     *
     * @return Referencia constante al vector de expresiones.
     *
     */
    const std::vector<std::unique_ptr<Expr>> &parts() const;

private:
    std::vector<std::unique_ptr<Expr>> parts_; ///< Lista de subexpresiones (texto y expresiones embebidas).
};

// Implementaciones inline

inline std::string FStringExpr::accept(const ExprVisitor &visitor) const { return visitor.visit(*this); }
inline Value FStringExpr::accept(InterpreterVisitor &visitor) const { return visitor.visitFStringExpr(*this); }
inline const std::vector<std::unique_ptr<Expr>> &FStringExpr::parts() const { return parts_; }

#endif