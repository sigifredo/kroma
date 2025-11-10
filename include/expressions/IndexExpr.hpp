/**
 * @file IndexExpr.hpp
 * @brief Declaración de la clase IndexExpr, que representa una operación de indexación `target[index]`.
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

#ifndef EXPRESSIONS_INDEXEXPR_HPP
#define EXPRESSIONS_INDEXEXPR_HPP

// own
#include <expressions/Expr.hpp>

/**
 * @class IndexExpr
 * @brief Representa una operación de indexación `target[index]`.
 *
 * Contiene:
 * - `target_`: expresión que evalúa al objeto indexable (lista, string...).
 * - `index_`: expresión que evalúa al índice.
 * - `bracketTok_`: token del `'['` para diagnóstico.
 */
class IndexExpr : public Expr
{
public:
    /**
     * @brief Construye una expresión de indexación.
     *
     * @param target Objeto sobre el que se accede.
     * @param index Índice o clave.
     * @param bracketTok Token del `'['`.
     *
     */
    IndexExpr(std::unique_ptr<Expr> target,
              std::unique_ptr<Expr> index,
              const Token &bracketTok)
        : target_(std::move(target)), index_(std::move(index)), bracketTok_(bracketTok) {}

    /**
     * @brief Acepta un visitante de tipo `ExprVisitor` (por ejemplo, para imprimir o serializar el AST).
     *
     * @param visitor Visitante concreto que implementa `visit(const IndexExpr&)`.
     *
     * @return Una representación textual del nodo, generada por el visitante.
     *
     */
    std::string accept(const ExprVisitor &visitor) const override;

    /**
     * @brief Acepta un visitante de tipo `InterpreterVisitor` (para evaluación en tiempo de ejecución).
     *
     * Este método ejecuta la lógica asociada al acceso por índice,
     * devolviendo el valor resultante de `target[index]`.
     *
     * @param visitor Intérprete o visitante de evaluación.
     *
     * @return El valor extraído del contenedor evaluado.
     *
     */
    Value accept(InterpreterVisitor &visitor) const override;

    /**
     * @brief Devuelve la expresión que produce el objeto indexable.
     *
     * @return Puntero a la subexpresión `target_`.
     *
     */
    Expr *target() const;

    /**
     * @brief Devuelve la expresión que produce el índice de acceso.
     *
     * @return Puntero a la subexpresión `index_`.
     *
     */
    Expr *index() const;

    /**
     * @brief Devuelve el token del corchete `'['` asociado a esta operación.
     *
     * Este token se usa para reportar errores con información de línea y columna.
     *
     * @return Referencia constante al token del corchete.
     *
     */
    const Token &token() const;

private:
    std::unique_ptr<Expr> target_; ///< Expresión que evalúa al objeto indexable.
    std::unique_ptr<Expr> index_;  ///< Expresión que evalúa al índice dentro del objeto.
    Token bracketTok_;             ///< Token `'['` para diagnóstico y trazabilidad.
};

// Implementaciones inline

inline std::string IndexExpr::accept(const ExprVisitor &visitor) const { return visitor.visit(*this); }
inline Value IndexExpr::accept(InterpreterVisitor &visitor) const { return Value(visitor.visitIndexExpr(*this)); }
inline Expr *IndexExpr::target() const { return target_.get(); }
inline Expr *IndexExpr::index() const { return index_.get(); }
inline const Token &IndexExpr::token() const { return bracketTok_; }

#endif
