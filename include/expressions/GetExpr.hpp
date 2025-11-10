/**
 * @file GetExpr.hpp
 * @brief Declaración de la clase GetExpr, que representa el acceso a una propiedad o atributo de un objeto en Kroma.
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

#ifndef EXPRESSIONS_GETEXPR_HPP
#define EXPRESSIONS_GETEXPR_HPP

// own
#include <expressions/Expr.hpp>

/**
 * @class GetExpr
 * @brief Clase que representa una expresión de acceso a propiedad u atributo en el AST de Kroma.
 *
 * La clase **GetExpr** modela el acceso a un campo o método dentro de un objeto.
 * Este nodo del AST se utiliza, por ejemplo, para acceder a propiedades de instancias
 * de clases definidas por el usuario o a miembros de módulos nativos.
 *
 * ### Ejemplo en código Kroma:
 * @code
 * class Punto {
 *     def init(x, y) {
 *         this.x = x
 *         this.y = y
 *     }
 * }
 *
 * let p = Punto(10, 20)
 * print(p.x)    # ← GetExpr
 * @endcode
 *
 * En este ejemplo, `p.x` se representa internamente como un nodo `GetExpr`.
 *
 * @see Expr
 * @see InterpreterVisitor
 * @see Token
 */
class GetExpr : public Expr
{
public:
    /**
     * @brief Constructor de GetExpr.
     *
     * @param object Expresión que representa el objeto del cual se obtiene la propiedad.
     * @param name Token que representa el nombre del atributo o método accedido.
     *
     */
    GetExpr(std::unique_ptr<Expr> object, const Token &name)
        : object_(std::move(object)), name_(name) {}

    /**
     * @brief Acepta un visitante que genera una representación textual del AST.
     *
     * @param visitor Visitante de tipo ExprVisitor.
     *
     * @return Representación textual del acceso a propiedad.
     *
     */
    std::string accept(const ExprVisitor &visitor) const override;

    /**
     * @brief Acepta un visitante intérprete que evalúa el acceso a propiedad.
     *
     * @param visitor Visitante de tipo InterpreterVisitor.
     *
     * @return Valor resultante del acceso.
     *
     */
    Value accept(InterpreterVisitor &visitor) const override;

    /**
     * @brief Devuelve la expresión que representa el objeto al que se accede.
     *
     * @return Puntero constante a la expresión del objeto.
     *
     */
    const Expr *object() const;

    /**
     * @brief Devuelve el token con el nombre del atributo o método accedido.
     *
     * @return Referencia constante al token del nombre.
     *
     */
    const Token &name() const;

private:
    std::unique_ptr<Expr> object_; ///< Expresión que representa el objeto base.
    Token name_;                   ///< Token del nombre de la propiedad o método accedido.
};

// Implementaciones inline

inline std::string GetExpr::accept(const ExprVisitor &visitor) const { return visitor.visit(*this); }
#warning "Implementar método GetExpr::accept(InterpreterVisitor &) correctamente"
inline Value GetExpr::accept(InterpreterVisitor &visitor) const { return Value("visitor.visitGetExpr(*this)"); }
inline const Expr *GetExpr::object() const { return object_.get(); }
inline const Token &GetExpr::name() const { return name_; }

#endif