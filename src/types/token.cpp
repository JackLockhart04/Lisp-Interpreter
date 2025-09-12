#include "token.h"
#include <sstream>

Token::Token(TokenType type, const std::string& lexeme, std::variant<std::monostate, double, std::string> literal, int line) {
    this->type = type;
    this->lexeme = lexeme;
    this->literal = literal;
    this->line = line;
}

Token::Token() {
    type = TokenType::NIL;
    lexeme = "";
    literal = std::monostate{};
    line = 0;
}

Token::TokenType Token::getType() const {
    return type;
}

std::string Token::getTypeString() const {
    switch (type) {
        case TokenType::LEFT_PAREN: return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN: return "RIGHT_PAREN";
        case TokenType::LEFT_BRACE: return "LEFT_BRACE";
        case TokenType::RIGHT_BRACE: return "RIGHT_BRACE";
        case TokenType::COMMA: return "COMMA";
        case TokenType::DOT: return "DOT";
        case TokenType::MINUS: return "MINUS";
        case TokenType::PLUS: return "PLUS";
        case TokenType::SEMICOLON: return "SEMICOLON";
        case TokenType::SLASH: return "SLASH";
        case TokenType::STAR: return "STAR";
        case TokenType::QUOTE: return "QUOTE";
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::SYMBOL: return "SYMBOL";
        case TokenType::LONG: return "LONG";
        case TokenType::DOUBLE: return "DOUBLE";
        case TokenType::STRING: return "STRING";
        case TokenType::NIL: return "NIL";
        case TokenType::EndOfFile: return "EndOfFile";
        case TokenType::WHITESPACE: return "Whitespace";
        case TokenType::NEWLINE: return "Newline";
        default: return "UNKNOWN";
    }
}

const std::string& Token::getLexeme() const {
    return lexeme;
}

const std::variant<std::monostate, double, std::string>& Token::getLiteral() const {
    return literal;
}

int Token::getLine() const {
    return line;
}

std::string Token::toString() const {
    std::string result = getTypeString();
    result += " '" + lexeme + "'";  
    if (std::holds_alternative<double>(literal)) {
        result += " " + std::to_string(std::get<double>(literal));
    } else if (std::holds_alternative<std::string>(literal)) {
        result += " \"" + std::get<std::string>(literal) + "\"";
    }
    return result;
}