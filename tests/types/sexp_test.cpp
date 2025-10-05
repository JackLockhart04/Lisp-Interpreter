#include "sexp_test.h"

// FIXME add more tests
void SexpTester::runTests(int &passes, int &fails) {
    testGetType(passes, fails);
    testGetAtom(passes, fails);
    testGetCons(passes, fails);
}

bool SexpTester::testGetType(int &passes, int &fails) {
    bool pass = true;
    // Create an atom and a cons cell
    SExpression* atomSExp = new SExpression(new Atom(1.0));
    SExpression* nilSExp = new SExpression(new Atom(Atom::Type::Nil));
    ConsCell* cons = new ConsCell(atomSExp, nilSExp);
    SExpression* consSExp = new SExpression(cons);

    // Test getType for atom
    if (atomSExp->getType() == SExpression::Type::Atom) {
        Logger::log("PASS: atom SExpression getType", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: atom SExpression getType", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Test getType for cons
    if (consSExp->getType() == SExpression::Type::ConsCell) {
        Logger::log("PASS: cons SExpression getType", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: cons SExpression getType", Logger::ERROR);
        fails++;
        pass = false;
    }

    return pass;
}

bool SexpTester::testGetAtom(int &passes, int &fails) {
    bool pass = true;
    // Create an atom and a cons cell
    Atom* testAtom = new Atom(1.0);
    SExpression* atomSExp = new SExpression(testAtom);

    // Test getAtom for atom
    Atom* retrievedAtom = nullptr;
    retrievedAtom = atomSExp->getAtom();
    if (retrievedAtom != nullptr 
            && retrievedAtom->getType() == testAtom->getType() 
            && retrievedAtom->getDouble() == testAtom->getDouble()) {
        Logger::log("PASS: atom SExpression getAtom", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: atom SExpression getAtom", Logger::ERROR);
        fails++;
        pass = false;
    }

    return pass;
}

bool SexpTester::testGetCons(int &passes, int &fails) {
    bool pass = true;

    // Create an atom and a cons cell
    Atom *atom1 = new Atom(1.0);
    Atom *atom2 = new Atom(Atom::Type::Nil);
    SExpression* atomSExp1 = new SExpression(atom1);
    SExpression* atomSExp2 = new SExpression(atom2);
    ConsCell* cons = new ConsCell(atomSExp1, atomSExp2);
    SExpression* consSExp = new SExpression(cons);

    // Test getCons for cons
    ConsCell* retrievedCons = nullptr;
    retrievedCons = consSExp->getCons();
    if (retrievedCons != nullptr 
            && retrievedCons->getCar()->getType() == atomSExp1->getType() 
            && retrievedCons->getCdr()->getType() == atomSExp2->getType()) {
        Logger::log("PASS: cons SExpression getCons", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: cons SExpression getCons", Logger::ERROR);
        fails++;
        pass = false;
    }

    return pass;
}