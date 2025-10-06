

#ifndef BASESCANNER_HPP
#define BASESCANNER_HPP

// own
#include <Token.hpp>

// std
#include <string>
#include <vector>

/**
 * @class BaseScanner
 * @brief Clase base abstracta para escáneres léxicos en Kroma.
 *
 * Define la interfaz común y funcionalidades básicas para cualquier escáner que procese
 * una cadena y genere una secuencia de tokens (`Token`). Las subclases deben implementar
 * el método `scanTokens()` para realizar el escaneo concreto.
 *
 */
class BaseScanner
{
public:
    /**
     * @brief Constructor explícito.
     *
     * Inicializa el escáner con el código fuente dado.
     *
     * @param src Cadena fuente a escanear.
     *
     */
    explicit BaseScanner(const std::string &src)
        : current_(0), line_(1), source_(src) {}

    /**
     * @brief Destructor virtual.
     *
     */
    virtual ~BaseScanner() = default;

protected:
    /**
     * @brief Avanza el cursor y retorna el carácter consumido.
     *
     * @return El carácter actual antes de avanzar.
     *
     */
    char advance();

    /**
     * @brief Verifica si se alcanzó el final del código fuente.
     *
     * @return `true` si ya no hay más caracteres por leer, `false` en caso contrario.
     *
     */
    bool isAtEnd() const;

    /**
     * @brief Verifica si el carácter actual coincide con el esperado. Si es así, avanza.
     *
     * @param expected Carácter esperado.
     *
     * @return `true` si coincide y avanza, `false` si no.
     *
     */
    bool match(const char &expected);

    /**
     * @brief Incrementa el contador de líneas.
     *
     */
    void newLine();

    /**
     * @brief Retorna el carácter actual sin consumirlo.
     *
     * @return Carácter en la posición actual del cursor.
     *
     */
    char peek() const;

    /**
     * @brief Retorna el siguiente carácter sin consumirlo.
     *
     * @return Carácter en la posición siguiente al cursor.
     *
     */
    char peekNext() const;

    /**
     * @brief Obtiene el índice actual del cursor.
     *
     * @return Posición actual como índice.
     *
     */
    size_t current() const;

    /**
     * @brief Obtiene el número actual de línea.
     *
     * @return Número de línea.
     *
     */
    int line() const;

    /**
     * @brief Devuelve una referencia al código fuente original.
     *
     * @return Referencia constante a la cadena fuente.
     *
     */
    const std::string &source() const;

private:
    size_t current_;     ///< Índice del carácter actual en la fuente.
    int line_;           ///< Número de línea actual (comienza en 1).
    std::string source_; ///< Cadena de texto que representa el código fuente a escanear.
};

inline size_t BaseScanner::current() const { return current_; }
inline int BaseScanner::line() const { return line_; }
inline const std::string &BaseScanner::source() const { return source_; }

#endif