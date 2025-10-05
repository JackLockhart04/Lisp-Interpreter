#include "parser.h"

Parser::Parser(const std::string& filename) {
    this->scanner = new Scanner(filename);
}

SExpression* Parser::parseSExpression() {
    Token token = scanner->nextToken();
    // Skip right parens
    while (token.getType() == Token::TokenType::RIGHT_PAREN) {
        token = scanner->nextToken();
    }

    SExpression* expr = nullptr;
    switch (token.getType()) {
        case Token::TokenType::DOUBLE: {
            double value = std::get<double>(token.getLiteral());
            Atom* atom = new Atom(value);
            expr = new SExpression(atom);
            break;
        }
        case Token::TokenType::LONG: {
            long value = static_cast<long>(std::get<double>(token.getLiteral()));
            Atom* atom = new Atom(value);
            expr = new SExpression(atom);
            break;
        }
        case Token::TokenType::STRING: {
            Atom* atom = new Atom(token.getLexeme(), Atom::Type::String);
            expr = new SExpression(atom);
            break;
        }
        case Token::TokenType::SYMBOL: {
            Atom* atom = new Atom(token.getLexeme(), Atom::Type::Symbol);
            expr = new SExpression(atom);
            break;
        }
        // List
        case Token::TokenType::LEFT_PAREN:
            expr = parseList();
            break;
        // Whitespace, newlines, and semicolons (comments)
        case Token::TokenType::SEMICOLON:
        case Token::TokenType::WHITESPACE:
        case Token::TokenType::NEWLINE:
            // Ignore and continue parsing
            expr = nullptr;
            break;
        // Math
        case Token::TokenType::PLUS:
        case Token::TokenType::MINUS:
        case Token::TokenType::STAR:
        case Token::TokenType::SLASH: {
            Atom* atom = new Atom(token.getLexeme(), Atom::Type::Symbol);
            expr = new SExpression(atom);
            break;
        }
        // QUOTE
        case Token::TokenType::QUOTE: {
            Atom* quoteAtom = new Atom("QUOTE", Atom::Type::Symbol);
            SExpression* quoteSExpr = new SExpression(quoteAtom);
            SExpression* quotedExpr = parseSExpression();
            ConsCell* cons = new ConsCell(quotedExpr, new SExpression());
            ConsCell* fullCons = new ConsCell(quoteSExpr, new SExpression(cons));
            expr = new SExpression(fullCons);
            break;
        }
        // EOF
        case Token::TokenType::EndOfFile: {
            Atom* atom = new Atom(Atom::Type::END_OF_FILE);
            expr = new SExpression(atom);
            break;
        }
        default:
            Logger::log("Unhandled parse token: " + token.toString(), Logger::ERROR);
            expr = nullptr;
    }

    return expr;
}

// Private
SExpression* Parser::parseList() {
    // Logger::log("Parser parsing list...", Logger::DEBUG);
    // If empty list
    if (scanner->peekToken().getType() == Token::TokenType::RIGHT_PAREN) {
        scanner->nextToken(); // Consume the right parenthesis
        Atom* atom = new Atom(Atom::Type::Nil);
        SExpression* expr = new SExpression(atom);
        return expr;
    }

    // Parse all elements into a vector
    std::vector<SExpression*> elements;
    while (scanner->peekToken().getType() != Token::TokenType::RIGHT_PAREN &&
           scanner->peekToken().getType() != Token::TokenType::EndOfFile) {
        auto expr = parseSExpression();
        // Skip null expressions
        if (expr) {
            elements.push_back(expr);
        }
    }
    scanner->nextToken(); // Consume the right parenthesis

    Logger::log("Parsed list with " + std::to_string(elements.size()) + " elements.", Logger::DEBUG);
    // Build cons cells from the back
    SExpression* list = new SExpression(new Atom(Atom::Type::Nil));
    for (auto it = elements.rbegin(); it != elements.rend(); ++it) {
        ConsCell* cons = new ConsCell(*it, list);
        list = new SExpression(cons);
    }
    return list;
}