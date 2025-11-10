/**
 * @file CallExpr.hpp
 * @brief Declaración de la clase CallExpr, que representa una llamada a función en el AST de Kroma.
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
 * @class CallExpr
 * @brief Clase que representa una expresión de llamada a función en el sistema de expresiones del intérprete de Kroma.
 *
 * La clase **CallExpr** modela la invocación de una función o método, almacenando
 * la expresión que representa al *callee* (función llamada), el paréntesis de cierre
 * para manejo de errores y los argumentos pasados a la llamada.
 *
 * ### Ejemplo en código Kroma:
 * @code
 * def sumar(a, b) {
 *     return a + b
 * }
 *
 * let resultado = sumar(5, 10)
 * @endcode
 *
 * En este caso, `sumar(5, 10)` se representa internamente como un nodo `CallExpr`.
 *
 * @see Expr
 * @see InterpreterVisitor
 * @see Token
 */

#ifndef EXPRESSION_CALLEXPR_HPP
#define EXPRESSION_CALLEXPR_HPP

// own
#include <expressions/Expr.hpp>

// std
#include <ranges>
#include <vector>

/**
 * @brief Nodo del AST que representa la llamada a una función o método.
 *
 * Un `CallExpr` contiene:
 * - Un callee (`Expr`) que identifica la función o expresión a invocar.
 * - Un token de cierre de paréntesis para referencia en mensajes de error.
 * - Una lista de argumentos, cada uno representado por una expresión (`Expr`).
 */
class CallExpr : public Expr
{
public:
    /**
     * @brief Constructor de CallExpr.
     *
     * @param callee Expresión que representa la función o método llamado.
     * @param paren Token que representa el paréntesis de cierre de la llamada.
     * @param arguments Lista de expresiones que representan los argumentos.
     *
     */
    CallExpr(std::unique_ptr<Expr> callee,
             const Token &paren,
             std::vector<std::unique_ptr<Expr>> arguments)
        : arguments_(std::move(arguments)), callee_(std::move(callee)), paren_(std::move(paren)) {}

    /**
     * @brief Acepta un visitante que genera una representación textual del AST.
     *
     * @param visitor Visitante de tipo ExprVisitor.
     *
     * @return Representación textual de la llamada a función.
     */
    std::string accept(const ExprVisitor &visitor) const override;

    /**
     * @brief Acepta un visitante intérprete que evalúa la llamada.
     *
     * @param visitor Visitante de tipo InterpreterVisitor.
     *
     * @return Valor resultante de la ejecución de la llamada.
     *
     */
    Value accept(InterpreterVisitor &visitor) const override;

    /**
     * @brief Devuelve el número de argumentos de la llamada.
     *
     * @return Cantidad de argumentos.
     *
     */
    size_t argumentCount() const;

    /**
     * @brief Devuelve un argumento por índice.
     *
     * @param index Índice del argumento (basado en 0).
     *
     * @return Puntero constante a la expresión del argumento.
     *
     * @throws std::out_of_range Si el índice es inválido.
     */
    const Expr *argument(const size_t &index) const;

    /**
     * @brief Devuelve un rango iterable con todos los argumentos.
     *
     * @return Rango de punteros a expresiones de los argumentos.
     *
     */
    auto arguments() const;

    /**
     * @brief Devuelve la expresión que representa la función llamada.
     *
     * @return Puntero constante a la expresión callee.
     *
     */
    const Expr *callee() const;

    /**
     * @brief Devuelve el token del paréntesis de cierre.
     *
     * @return Referencia constante al token paren.
     *
     */
    const Token &paren() const;

private:
    std::vector<std::unique_ptr<Expr>> arguments_; ///< Lista de expresiones que representan los argumentos.
    std::unique_ptr<Expr> callee_;                 ///< Expresión que representa la función o método llamado.
    Token paren_;                                  ///< Token del paréntesis de cierre (para mensajes de error).
};

// Implementaciones inline

inline std::string CallExpr::accept(const ExprVisitor &visitor) const { return visitor.visit(*this); }
#warning "Implementar método CallExpr::accept(InterpreterVisitor &) correctamente"
inline Value CallExpr::accept(InterpreterVisitor &) const { return Value("visitor.visitCallExpr(*this)"); }
inline size_t CallExpr::argumentCount() const { return arguments_.size(); }
inline const Expr *CallExpr::argument(const size_t &index) const { return arguments_.at(index).get(); }
inline auto CallExpr::arguments() const
{
    return arguments_ | std::views::transform([](const std::unique_ptr<Expr> &arg)
                                              { return arg.get(); });
}
inline const Expr *CallExpr::callee() const { return callee_.get(); }
inline const Token &CallExpr::paren() const { return paren_; }

#endif
