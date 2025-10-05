#include "type_checker_test.h"

TypeCheckerTester::TypeCheckerTester() {
}

bool TypeCheckerTester::runTest(int &passes, int &fails) {
    bool allPassed = true;
    allPassed &= testIsNil(passes, fails);
    allPassed &= testIsNumber(passes, fails);
    allPassed &= testIsSymbol(passes, fails);
    allPassed &= testIsString(passes, fails);
    allPassed &= testIsList(passes, fails);
    return allPassed;
}

bool TypeCheckerTester::testIsNil(int &passes, int &fails) {
    bool pass = true;
    // Create a unique_ptr to a nil Atom
    Atom* nilAtom = new Atom();
    SExpression nilExpr(std::move(nilAtom));
    if (TypeChecker::isNil(&nilExpr)) {
        Logger::log("PASS: Nil expression is correctly identified as nil.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Nil expression is NOT identified as nil.", Logger::ERROR);
        fails++;
        pass = false;
    }
    long num = 42;
    Atom* numAtom = new Atom(num);
    SExpression numExpr(std::move(numAtom));
    if (!TypeChecker::isNil(&numExpr)) {
        Logger::log("PASS: Number expression is correctly identified as NOT nil.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Number expression is incorrectly identified as NOT nil.", Logger::ERROR);
        fails++;
        pass = false;
    }

    return pass;
}

bool TypeCheckerTester::testIsNumber(int &passes, int &fails){
    bool pass = true;
    long num = 42;
    Atom* numAtom = new Atom(num);
    SExpression numExpr(numAtom);
    if (TypeChecker::isNumber(&numExpr)) {
        Logger::log("PASS: Long expression is correctly identified as number.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Long expression is NOT identified as number.", Logger::ERROR);
        fails++;
        pass = false;
    }
    double dnum = 3.14;
    Atom* dnumAtom = new Atom(dnum);
    SExpression dnumExpr(dnumAtom);
    if (TypeChecker::isNumber(&dnumExpr)) {
        Logger::log("PASS: Double expression is correctly identified as number.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Double expression is NOT identified as number.", Logger::ERROR);
        fails++;
        pass = false;
    }
    // See if string is seen as a number
    Atom* strAtom = new Atom("myString", Atom::Type::String);
    SExpression strExpr(strAtom);
    if (!TypeChecker::isNumber(&strExpr)) {
        Logger::log("PASS: String expression is correctly identified as NOT number.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: String expression is incorrectly identified as number.", Logger::ERROR);
        fails++;
        pass = false;
    }

    return pass;
}

bool TypeCheckerTester::testIsSymbol(int &passes, int &fails){
    bool pass = true;
    // Symbol
    Atom* symAtom = new Atom("mySymbol", Atom::Type::Symbol);
    SExpression symExpr(symAtom);
    if (TypeChecker::isSymbol(&symExpr)) {
        Logger::log("PASS: Symbol expression is correctly identified as symbol.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Symbol expression is incorrectly identified as NOT symbol.", Logger::ERROR);
        fails++;
        pass = false;
    }
    // Test string
    Atom* strAtom = new Atom("myString", Atom::Type::String);
    SExpression strExpr(strAtom);
    if (!TypeChecker::isSymbol(&strExpr)) {
        Logger::log("PASS: String expression is correctly identified as NOT symbol.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: String expression is incorrectly identified as symbol.", Logger::ERROR);
        fails++;
        pass = false;
    }

    return pass;
}

bool TypeCheckerTester::testIsString(int &passes, int &fails){
    bool pass = true;
    // String test
    Atom* strAtom = new Atom("myString", Atom::Type::String);
    SExpression strExpr(strAtom);
    if (TypeChecker::isString(&strExpr)) {
        Logger::log("PASS: String expression is correctly identified as string.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: String expression is incorrectly identified as string.", Logger::ERROR);
        fails++;
        pass = false;
    }
    // Num as string
    long num = 42;
    Atom* numAtom = new Atom(num);
    SExpression numExpr(numAtom);
    if (!TypeChecker::isString(&numExpr)) {
        Logger::log("PASS: Number expression is correctly identified as NOT string.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Number expression is incorrectly identified as string.", Logger::ERROR);
        fails++;
        pass = false;
    }

    return pass;
}

bool TypeCheckerTester::testIsList(int &passes, int &fails){
    bool pass = true;
    // FIXME make a cons cell to test
    Atom* carAtom = new Atom(1L);
    SExpression* carExpr = new SExpression(carAtom);
    Atom* cdrAtom = new Atom();
    SExpression* cdrExpr = new SExpression(cdrAtom);
    ConsCell* consCell = new ConsCell(carExpr, cdrExpr);
    SExpression* consExpr = new SExpression(consCell);
    if (TypeChecker::isList(consExpr)) {
        Logger::log("PASS: Cons cell expression is correctly identified as list.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Cons cell expression is NOT identified as list.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Test nil as list
    Atom* nilAtom = new Atom();
    SExpression nilExpr(nilAtom);
    if (TypeChecker::isList(&nilExpr)) {
        Logger::log("PASS: Nil expression is correctly identified as list.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Nil expression is NOT identified as list.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Test num as list
    long num = 42;
    Atom* numAtom = new Atom(num);
    SExpression numExpr(numAtom);
    if (!TypeChecker::isList(&numExpr)) {
        Logger::log("PASS: Number expression is correctly identified as NOT list.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Number expression is NOT identified as list.", Logger::ERROR);
        fails++;
        pass = false;
    }

    return pass;
}