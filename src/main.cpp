#include "parser.h"

#include <iostream>

Logger::LogLevel logLevel = Logger::INFO;

int main(int argc, char** argv) {
    Logger::setLogLevel(logLevel);
    std::string filename = (argc > 1) ? argv[1] : "";
    Parser parser(filename);

    while(true) {
        SExpression* expr = parser.parseSExpression();
        if (!expr || expr == nullptr) continue; // Skip null expressions
        // Print gotten sexpression
        if (expr->getType() == SExpression::Type::Atom
                    && expr->getAtom()->getType() == Atom::Type::END_OF_FILE) {
            Logger::log("Main found EOF atom", Logger::DEBUG);
            break;
        }
        std::cout << ": ";
        expr->print();
        std::cout << std::endl;
    }

    Logger::log("Exiting normally.", Logger::INFO);

    return 0;
}
