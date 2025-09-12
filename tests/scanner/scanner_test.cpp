#include "scanner_test.h"

bool ScannerTester::runTest(int &passes, int &fails) {
    Scanner scanner("../tests/scanner/test_cases.txt");

    bool pass = true;
    // 42
    pass &= compare("42", Token::TokenType::LONG, scanner);
    // 1.2
    pass &= compare("1.2", Token::TokenType::DOUBLE, scanner);
    // 1.2.3
    pass &= compare("1.2", Token::TokenType::DOUBLE, scanner);
    pass &= compare(".3", Token::TokenType::DOUBLE, scanner);
    // Hello world; this shouldn't print
    pass &= compare("Hello", Token::TokenType::SYMBOL, scanner);
    pass &= compare("world", Token::TokenType::SYMBOL, scanner);
    pass &= compare(";", Token::TokenType::SEMICOLON, scanner);
    // "Roll tide"
    pass &= compare("Roll tide", Token::TokenType::STRING, scanner);
    // (Roll tide)
    pass &= compare("(", Token::TokenType::LEFT_PAREN, scanner);
    pass &= compare("Roll", Token::TokenType::SYMBOL, scanner);
    pass &= compare("tide", Token::TokenType::SYMBOL, scanner);
    pass &= compare(")", Token::TokenType::RIGHT_PAREN, scanner);
    /*
    ( (1)
    (2)
    (3) )
    */
    pass &= compare("(", Token::TokenType::LEFT_PAREN, scanner);
    pass &= compare("(", Token::TokenType::LEFT_PAREN, scanner);
    pass &= compare("1", Token::TokenType::LONG, scanner);
    pass &= compare(")", Token::TokenType::RIGHT_PAREN, scanner);
    pass &= compare("(", Token::TokenType::LEFT_PAREN, scanner);
    pass &= compare("2", Token::TokenType::LONG, scanner);
    pass &= compare(")", Token::TokenType::RIGHT_PAREN, scanner);
    pass &= compare("(", Token::TokenType::LEFT_PAREN, scanner);
    pass &= compare("3", Token::TokenType::LONG, scanner);
    pass &= compare(")", Token::TokenType::RIGHT_PAREN, scanner);
    pass &= compare(")", Token::TokenType::RIGHT_PAREN, scanner);

    // Finish
    if (pass) {
        Logger::log("PASS: Scanner tests passed.", Logger::INFO);
        passes++;
        return true;
    } else {
        Logger::log("FAIL: Scanner tests failed.", Logger::ERROR);
        fails++;
        return false;
    }
}

Token ScannerTester::getNextNonWhitespaceToken(Scanner &scanner) {
    Token token = scanner.nextToken();
    while (token.getType() == Token::TokenType::NEWLINE || token.getType() == Token::TokenType::WHITESPACE) {
        token = scanner.nextToken();
    }
    return token;
}

bool ScannerTester::compare(std::string lexeme, Token::TokenType type, Scanner &scanner) {
    Token current = getNextNonWhitespaceToken(scanner);
    if (current.getType() != type || current.getLexeme() != lexeme) {
        Logger::log("FAIL: Token is not '" + lexeme + "', instead is '" + current.getLexeme() + "' of type " + current.getTypeString(), Logger::ERROR);
        return false;
    }
    return true;
}