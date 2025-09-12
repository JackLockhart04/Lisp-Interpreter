#include "reader/reader_test.h"
#include "scanner/scanner_test.h"
#include "types/atom_test.h"
#include "types/cons_test.h"
#include "types/sexp_test.h"
// #include "core/type_checker/type_checker_test.h"

#include "util/logger/logger.h"

int main(int argc, char *argv[]) {
    // DEBUG for all messages, INFO for general testing, ERROR for only fails
    Logger::setLogLevel(Logger::INFO);
    Logger::log("Starting tests...");

    int passes = 0;
    int fails = 0;

    Logger::log("----- Input handling Tests -----", Logger::INFO);
    ReaderTester::runTest(passes, fails);
    ScannerTester::runTest(passes, fails);

    Logger::log("----- Atom tests -----", Logger::INFO);
    AtomTester::runTests(passes, fails);

    Logger::log("----- Cons tests -----", Logger::INFO);
    ConsTester::runTests(passes, fails);

    Logger::log("----- SExpression tests -----", Logger::INFO);
    SexpTester::runTests(passes, fails);

    // Logger::log("----- TypeChecker tests -----", Logger::INFO);
    // TypeCheckerTester::runTest(passes, fails);

    Logger::log("Tests complete.", Logger::INFO);
    Logger::log("Passes: " + std::to_string(passes), Logger::INFO);
    Logger::log("Fails: " + std::to_string(fails), Logger::INFO);
}
