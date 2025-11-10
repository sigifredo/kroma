/**
 * @file ExprVisitor.hpp
 * @brief Declaración de la clase base abstracta ExprVisitor, usada para recorrer expresiones del AST de Kroma.
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

#ifndef EXPRESSIONS_EXPRVISITOR_HPP
#define EXPRESSIONS_EXPRVISITOR_HPP

// std
#include <string>

class AssignExpr;
class BinaryExpr;
class CallExpr;
class FStringExpr;
class GetExpr;
class GroupingExpr;
class IndexExpr;
class ListExpr;
class LiteralExpr;
class LogicalExpr;
class RangeExpr;
class UnaryExpr;
class VariableExpr;

/**
 * @class ExprVisitor
 * @brief Interfaz base del patrón *Visitor* para recorrer y procesar expresiones del AST.
 *
 * La clase **ExprVisitor** define la interfaz que permite aplicar operaciones sobre
 * los distintos tipos de expresiones de Kroma sin modificar sus clases concretas.
 *
 * Cada subclase de `Expr` (como `BinaryExpr`, `LiteralExpr`, `CallExpr`, etc.)
 * implementa un método `accept()` que invoca el `visit()` correspondiente en el visitante.
 *
 * Esto permite separar la lógica de representación, análisis o interpretación del propio AST.
 *
 * ### Ejemplo de uso
 * @code
 * class AstPrinter : public ExprVisitor {
 * public:
 *     std::string visit(const BinaryExpr &expr) const override {
 *         return "( " + expr.left()->toString() + " " + expr.op().lexeme() + " " + expr.right()->toString() + " )";
 *     }
 *     // ... otros visit() ...
 * };
 * @endcode
 *
 * @see Expr
 * @see InterpreterVisitor
 * @see AssignExpr
 * @see BinaryExpr
 * @see CallExpr
 * @see LiteralExpr
 */
class ExprVisitor
{
public:
    /// Constructor por defecto.
    ExprVisitor() = default;

    /// Destructor virtual para permitir destrucción polimórfica.
    virtual ~ExprVisitor() = default;

    /**
     * @name Métodos de visita
     * Cada método corresponde a un tipo concreto de expresión dentro del AST.
     * @{
     */
    virtual std::string visit(const AssignExpr &expr) const = 0;   ///< Visita una expresión de asignación.
    virtual std::string visit(const BinaryExpr &expr) const = 0;   ///< Visita una expresión binaria.
    virtual std::string visit(const CallExpr &expr) const = 0;     ///< Visita una llamada a función.
    virtual std::string visit(const FStringExpr &expr) const = 0;  ///< Visita una interpolación de string (f-string).
    virtual std::string visit(const GetExpr &expr) const = 0;      ///< Visita una expresión de acceso a propiedad.
    virtual std::string visit(const GroupingExpr &expr) const = 0; ///< Visita una agrupación de expresiones.
    virtual std::string visit(const IndexExpr &expr) const = 0;    ///< Visita un acceso por índice.
    virtual std::string visit(const ListExpr &expr) const = 0;     ///< Visita una lista literal.
    virtual std::string visit(const LiteralExpr &expr) const = 0;  ///< Visita un literal (número, texto, etc.).
    virtual std::string visit(const LogicalExpr &expr) const = 0;  ///< Visita una expresión lógica (and, or).
    virtual std::string visit(const RangeExpr &expr) const = 0;    ///< Visita una expresión de rango (a..b).
    virtual std::string visit(const UnaryExpr &expr) const = 0;    ///< Visita una expresión unaria.
    virtual std::string visit(const VariableExpr &expr) const = 0; ///< Visita una variable.
    /** @} */
};

#endif