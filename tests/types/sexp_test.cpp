
#include "sexp_test.h"

void SexpTester::runTests(int &passes, int &fails) {
    testGetType(passes, fails);
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
    Atom* atom = new Atom(1.0);
    SExpression* atomSExp = new SExpression(atom);
    SExpression* nilSExp = new SExpression(new Atom(Atom::Type::Nil));
    ConsCell* cons = new ConsCell(atomSExp, nilSExp);
    SExpression* consSExp = new SExpression(cons);

    // Test getAtom for atom
    Atom* retrievedAtom = nullptr;
    retrievedAtom = atomSExp->getAtom();

    return pass;
}

bool SexpTester::testGetCons(int &passes, int &fails) {
    bool pass = true;
    return pass;
}