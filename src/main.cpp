#include "input/parser.h"
#include "core/eval.h"
#include "core/environment.h"

#include <iostream>

Logger::LogLevel logLevel = Logger::INFO;

int main(int argc, char** argv) {
    Logger::setLogLevel(logLevel);
    std::string filename = (argc > 1) ? argv[1] : "";
    Parser parser(filename);

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
