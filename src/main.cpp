#include "input/parser.h"
#include "core/eval.h"
#include "core/environment.h"

#include <iostream>

Logger::LogLevel logLevel = Logger::INFO;

int main() {
    Logger::setLogLevel(logLevel);
    Parser parser;

    Environment globalEnv;

    while(true) {
        SExpression* expr = parser.parseSExpression();
        if (!expr || expr == nullptr) continue; // Skip null expressions
        // Check for end of file atom
        if (expr->getType() == SExpression::Type::Atom
                    && expr->getAtom()->getType() == Atom::Type::END_OF_FILE) {
            Logger::log("Main found EOF atom", Logger::DEBUG);
            break;
        }

        // Eval the expression
        SExpression *result = eval(expr, &globalEnv);
        std::cout << ": ";
        result->print();
        std::cout << std::endl;
    }

    Logger::log("Exiting normally.", Logger::INFO);

    return 0;
}
