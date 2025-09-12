#include "cons_test.h"

void ConsTester::runTests(int &passes, int &fails) {
    testCadr(passes, fails);
    testToVector(passes, fails);
}

bool ConsTester::testCadr(int &passes, int &fails) {
    bool pass = true;
    // Create atoms
    Atom* atom1 = new Atom("First", Atom::Type::Symbol);
    Atom* atom2 = new Atom("Second", Atom::Type::Symbol);
    Atom* atom3 = new Atom("Third", Atom::Type::Symbol);

    // Create SExpressions for atoms
    SExpression* sexpr1 = new SExpression(atom1);
    SExpression* sexpr2 = new SExpression(atom2);
    SExpression* sexpr3 = new SExpression(atom3);

    // Build cons cells from the back
    SExpression* listItem = new SExpression(new Atom(Atom::Type::Nil));
    ConsCell* cons = new ConsCell(sexpr3, listItem);
    listItem = new SExpression(cons);
    cons = new ConsCell(sexpr2, listItem);
    listItem = new SExpression(cons);
    cons = new ConsCell(sexpr1, listItem);

    // Test car
    SExpression const* car = &cons->getCar();
    if (car == sexpr1) {
        Logger::log("PASS: car", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: car", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Test cdr
    SExpression const* cdr = &cons->getCdr();
    if (cdr == listItem) {
        Logger::log("PASS: cdr", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: cdr", Logger::ERROR);
        fails++;
        pass = false;
    }

    return pass;
}

bool ConsTester::testToVector(int &passes, int &fails) {
    bool pass = true;
    // Create atoms
    Atom* atom1 = new Atom("First", Atom::Type::Symbol);
    Atom* atom2 = new Atom("Second", Atom::Type::Symbol);
    Atom* atom3 = new Atom("Third", Atom::Type::Symbol);

    // Create SExpressions for atoms
    SExpression* sexpr1 = new SExpression(atom1);
    SExpression* sexpr2 = new SExpression(atom2);
    SExpression* sexpr3 = new SExpression(atom3);

    // Build cons cells from the back
    SExpression* listItem = new SExpression(new Atom(Atom::Type::Nil));
    ConsCell* cons = new ConsCell(sexpr3, listItem);
    listItem = new SExpression(cons);
    cons = new ConsCell(sexpr2, listItem);
    listItem = new SExpression(cons);
    cons = new ConsCell(sexpr1, listItem);

    // Convert to vector
    std::vector<SExpression*> vec = cons->toVector();

    // Check size
    if (vec.size() == 4) { // 3 atoms + 1 nil
        Logger::log("PASS: toVector size", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: toVector size", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Check contents
    if (vec[0] == sexpr1 && vec[1] == sexpr2 && vec[2] == sexpr3 && vec[3]->getType() == SExpression::Type::Atom && vec[3]->getAtom()->getType() == Atom::Type::Nil) {
        Logger::log("PASS: toVector contents", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: toVector contents", Logger::ERROR);
        fails++;
        pass = false;
    }

    return pass;
}