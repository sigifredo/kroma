

#ifndef TOKEN_HPP
#define TOKEN_HPP

// own
#include <TokenType.hpp>
#include <Value.hpp>

// std
#include <string>

/**
 * @class Token
 * @brief Represents a lexical token in the Kroma programming language.
 *
 * A Token contains information about a lexeme found during scanning, including its type,
 * literal value (if any), line number, and the exact string representation.
 */
class Token
{
public:
    /**
     * @brief Default constructor.
     */
    Token() = default;

    /**
     * @brief Copy constructor.
     *
     * @param other The token to copy.
     */
    Token(const Token &other) = default;

    /**
     * @brief Constructs a token with the given attributes.
     *
     * @param type The type of token.
     * @param lexeme The lexeme string as found in the source code.
     * @param literal The optional literal value (e.g., number, string).
     * @param line The line number where the token was found.
     */
    Token(const TokenType &type,
          const std::string &lexeme,
          const Value &literal = Value(),
          const int &line = 0)
        : lexeme_(lexeme),
          line_(line),
          literal_(literal),
          type_(type) {}

    /**
     * @brief Assignment operator.
     *
     * @param other The token to assign from.
     * @return Reference to this token.
     */
    Token &operator=(const Token &other) = default;

    /**
     * @brief Returns a string representation of the token.
     *
     * @return A formatted string representing the token.
     */
    std::string toString() const;

    /**
     * @brief Gets the lexeme (original text) of the token.
     *
     * @return The lexeme as a string.
     */
    std::string lexeme() const;

    /**
     * @brief Gets the line number where the token was found.
     *
     * @return Line number in the source code.
     */
    int line() const;

    /**
     * @brief Gets the literal value of the token.
     *
     * @return A constant reference to the literal value.
     */
    const Value &literal() const;

    /**
     * @brief Gets the type of the token.
     *
     * @return The token type.
     */
    TokenType type() const;

    /**
     * @brief Stream output operator for Token.
     *
     * Allows a Token to be printed using an output stream, such as `std::cout`.
     * This is typically used for debugging or logging purposes.
     *
     * @param os The output stream.
     * @param token The Token to print.
     * @return Reference to the output stream after writing the Token.
     *
     * @example
     * Token token(TokenType::IDENTIFIER, "nombre", Value(), 1);
     * std::cout << token << std::endl;
     */
    friend std::ostream &operator<<(std::ostream &os, const Token &token);

private:
    std::string lexeme_; ///< The lexeme string as it appears in source.
    int line_;           ///< The line number where this token occurs.
    Value literal_;      ///< The literal value (if any) represented by the token.
    TokenType type_;     ///< The type/category of the token.
};

inline std::string Token::toString() const { return std::to_string(static_cast<int>(type_)) + " (" + lexeme_ + ")"; }
inline std::string Token::lexeme() const { return lexeme_; }
inline int Token::line() const { return line_; }
inline const Value &Token::literal() const { return literal_; }
inline TokenType Token::type() const { return type_; }

#endif