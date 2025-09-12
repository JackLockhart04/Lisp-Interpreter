#pragma once
#include <string>
#include <variant>

class Token {
public:
    enum class TokenType {
        // Add your token types here, e.g. IDENTIFIER, NUMBER, STRING, etc.
        // Single Characters
        LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, 
        COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,
        QUOTE,

        // Operators
        IDENTIFIER,
        // Data types
        SYMBOL, LONG, DOUBLE, STRING, NIL,

        // ...
        EndOfFile, WHITESPACE, NEWLINE
    };

    Token(); // Default constructor for a null token
    Token(TokenType type, const std::string& lexeme, std::variant<std::monostate, double, std::string> literal, int line);
    TokenType getType() const;
    std::string getTypeString() const;
    const std::string& getLexeme() const;
    const std::variant<std::monostate, double, std::string>& getLiteral() const;
    int getLine() const;
    std::string toString() const;
private:
    TokenType type;
    std::string lexeme;
    std::variant<std::monostate, double, std::string> literal;
    int line;
};
