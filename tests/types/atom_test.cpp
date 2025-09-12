
#include "atom_test.h"
#include "types/atom.h"

void AtomTester::runTests(int &passes, int &fails) {
    testGetValue(passes, fails);
}

bool AtomTester::testGetValue(int &passes, int &fails) {
    bool pass = true;
    Atom strAtom("test", Atom::Type::String);
    if (strAtom.getString() == "test") {
        Logger::log("PASS: getString", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: getString", Logger::ERROR);
        fails++;
        pass = false;
    }

    Atom symAtom("symbol", Atom::Type::Symbol);
    if (symAtom.getSymbol() == "symbol") {
        Logger::log("PASS: getSymbol", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: getSymbol", Logger::ERROR);
        fails++;
        pass = false;
    }

    long intValue = 42;
    Atom intAtom(intValue);
    if (intAtom.getLong() == 42) {
        Logger::log("PASS: getLong", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: getLong", Logger::ERROR);
        fails++;
        pass = false;
    }

    double floatValue = 3.14;
    Atom floatAtom(floatValue);
    if (floatAtom.getDouble() == 3.14) {
        Logger::log("PASS: getDouble", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: getDouble", Logger::ERROR);
        fails++;
        pass = false;
    }

    Atom nilAtom(Atom::Type::Nil);
    if (nilAtom.getType() == Atom::Type::Nil) {
        Logger::log("PASS: getType", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: getType", Logger::ERROR);
        fails++;
        pass = false;
    }

    return pass;
}

bool AtomTester::testGetType(int &passes, int &fails) {
    bool pass = true;

    Atom strAtom("test", Atom::Type::String);
    if (strAtom.getType() == Atom::Type::String) {
        Logger::log("PASS: getType for String", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: getType for String", Logger::ERROR);
        fails++;
        pass = false;
    }

    Atom symAtom("symbol", Atom::Type::Symbol);
    if (symAtom.getType() == Atom::Type::Symbol) {
        Logger::log("PASS: getType for Symbol", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: getType for Symbol", Logger::ERROR);
        fails++;
        pass = false;
    }

    long intValue = 42;
    Atom intAtom(intValue);
    if (intAtom.getType() == Atom::Type::Long) {
        Logger::log("PASS: getType for Long", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: getType for Long", Logger::ERROR);
        fails++;
        pass = false;
    }

    double floatValue = 3.14;
    Atom floatAtom(floatValue);
    if (floatAtom.getType() == Atom::Type::Double) {
        Logger::log("PASS: getType for Double", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: getType for Double", Logger::ERROR);
        fails++;
        pass = false;
    }

    Atom nilAtom(Atom::Type::Nil);
    if (nilAtom.getType() == Atom::Type::Nil) {
        Logger::log("PASS: getType for Nil", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: getType for Nil", Logger::ERROR);
        fails++;
        pass = false;
    }

    return pass;
}