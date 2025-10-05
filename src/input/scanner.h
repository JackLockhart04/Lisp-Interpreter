#pragma once

#include "types/token.h"
#include "input/reader.h"

#include <string>
#include <vector>
#include <unordered_map>

class Scanner {
public:
    Scanner(const std::string& filename = "", int line = 1);
    Token nextToken(); // Returns the next token from the input
    bool isAtEnd() const;
    bool hasError() const { return hasErrorFlag; }
    std::string getErrorMessage() const { return errorMessage; }

    // For peeking
    Token peekToken();

private:
    Reader *reader;
    size_t start;
    size_t current;
    int line;
    bool isAtEndFlag;
    std::string source;
    bool hasErrorFlag;
    std::string errorMessage;
    std::unordered_map<std::string, Token::TokenType> singleCharTokenTypeMap;

    // Methods
    int initTokenTypeMap();

    // Symbol methods
    bool isSymbolStart(char ch);
    bool isSymbolPart(char ch);

    bool isWhiteSpace(char ch);

    // For peeking
    Token peekedToken;
    bool hasPeeked = false;
};