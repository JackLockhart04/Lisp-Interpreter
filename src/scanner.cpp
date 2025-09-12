#include "scanner.h"

Scanner::Scanner(const std::string& filename, int line) {
    reader = new Reader(filename);
    if (reader->hasError()) {
        // Handle error (e.g., log it, throw an exception, etc.)
        hasErrorFlag = true;
        errorMessage = reader->getErrorMessage();
    } else {
        hasErrorFlag = false;
        errorMessage.clear();
    }
    start = 0;
    current = 0;
    this->line = line;
    isAtEndFlag = false;
    hasPeeked = false;
    initTokenTypeMap();
}

Token Scanner::nextToken() {
    if (hasPeeked) {
        hasPeeked = false;
        return peekedToken;
    }
    // Skip all leading whitespace using isWhiteSpace
    char ch = reader->next();
    // Logger::log(std::string("Scanning character: '") + ch + "'", Logger::DEBUG);
    while (isWhiteSpace(ch)) {
        ch = reader->next();
    }
    if (ch == EOF) {
        isAtEndFlag = true;
        return Token(Token::TokenType::EndOfFile, "", std::monostate{}, line);
    }
    // Convert to a string
    std::string tokenLexeme(1, ch);

    // Check for numbers
    // If digit, then - and a digit, then + and a digit, then . and a digit
    if (isdigit(ch) || (ch == '-' && isdigit(reader->peek())) || 
        (ch == '+' && isdigit(reader->peek())) || (ch == '.' && isdigit(reader->peek()))) {
        tokenLexeme = ch;
        // More digits or decimal
        bool decimal = false;
        if(ch == '.') decimal = true;
        while (isdigit(reader->peek()) || (reader->peek() == '.')) {
            if (reader->peek() == '.') {
                // Stop at second decimal (FIXME to have an error)
                if(decimal) break;
                // First decimal
                decimal = true;
            }
            tokenLexeme += reader->next();
        }
        if (decimal) {
            // It's a double
            return Token(Token::TokenType::DOUBLE, tokenLexeme, std::stod(tokenLexeme), line);
        } else {
            // It's a long
            return Token(Token::TokenType::LONG, tokenLexeme, static_cast<double>(std::stol(tokenLexeme)), line);
        }
    }

    // Check for string
    if (ch == '"') {
        tokenLexeme = "";
        while (reader->peek() != '"' && reader->peek() != EOF) {
            tokenLexeme += reader->next();
        }
        reader->next(); // Consume closing "
        return Token(Token::TokenType::STRING, tokenLexeme, std::monostate{}, line);
    }

    // Check if its a 1-character token
    auto it = singleCharTokenTypeMap.find(tokenLexeme);
    if (it != singleCharTokenTypeMap.end()) {
        // Ignore comments
        if (it->second == Token::TokenType::SEMICOLON) {
            // Ignore rest of line
            while (reader->next() != '\n' && reader->peek() != EOF);
        }
        // Return token
        return Token(it->second, tokenLexeme, std::monostate{}, line);
    }

    // Check for symbols
    if (isSymbolStart(ch)) {
        // Get chars until delimiter
        while (isSymbolPart(reader->peek())) {
            tokenLexeme += reader->next();
        }
        Logger::log("Scanned symbol: " + tokenLexeme, Logger::DEBUG);
        return Token(Token::TokenType::SYMBOL, tokenLexeme, std::monostate{}, line);
    }

    // Check for whitespace
    if(ch == '\n') {
        line++;
        return Token(Token::TokenType::NEWLINE, tokenLexeme, std::monostate{}, line);
    }

    return Token(Token::TokenType::IDENTIFIER, tokenLexeme, std::monostate{}, line);
}

Token Scanner::peekToken() {
    if (!hasPeeked) {
        peekedToken = nextToken();
        hasPeeked = true;
    }
    // Logger::log("Peeked token: " + peekedToken.toString(), Logger::DEBUG);
    return peekedToken;
}

bool Scanner::isSymbolStart(char ch) {
    std::string s(1, ch);
    if (singleCharTokenTypeMap.find(s) != singleCharTokenTypeMap.end()) return false;
    if (isspace(ch) || isdigit(ch) || ch == '"' || ch == '\'') return false;
    return true;
}
bool Scanner::isSymbolPart(char ch) {
    std::string s(1, ch);
    if (singleCharTokenTypeMap.find(s) != singleCharTokenTypeMap.end()) return false;
    if (isspace(ch) || ch == '"' || ch == '\'' || ch == EOF) return false;
    return true;
}
bool Scanner::isWhiteSpace(char ch) {
    return ch == ' ' || ch == '\t';
}

bool Scanner::isAtEnd() const {
    return isAtEndFlag;
}

// Private methods
int Scanner::initTokenTypeMap() {
    singleCharTokenTypeMap = std::unordered_map<std::string, Token::TokenType>{
        {"(", Token::TokenType::LEFT_PAREN},
        {")", Token::TokenType::RIGHT_PAREN},
        {"{", Token::TokenType::LEFT_BRACE},
        {"}", Token::TokenType::RIGHT_BRACE},
        {",", Token::TokenType::COMMA},
        {".", Token::TokenType::DOT},
        {"-", Token::TokenType::MINUS},
        {"+", Token::TokenType::PLUS},
        {";", Token::TokenType::SEMICOLON},
        {"/", Token::TokenType::SLASH},
        {"*", Token::TokenType::STAR},
        // Add more tokens as needed
    };
    return 0; // Placeholder
}