#pragma once

#include "util/logger.h"
#include "input/scanner.h"

#include <iostream>
#include <fstream>
#include <string>
#include <memory>


class ScannerTester {
public:
    static bool runTest(int &passes, int &fails);
private:
    static Token getNextNonWhitespaceToken(Scanner &scanner);
    static bool compare(std::string lexeme, Token::TokenType type, Scanner &scanner);
};