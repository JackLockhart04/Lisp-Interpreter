#include "environment_test.h"

bool EnvironmentTester::runTests(int &passes, int &fails) {
    bool allPassed = true;
    allPassed &= testLookup(passes, fails);
    
    return allPassed;
}

bool EnvironmentTester::testLookup(int &passes, int &fails) {
    bool pass = true;

    // Create an environment and add some variables
    Environment env;

    SExpression *var1 = new SExpression(new Atom("x", Atom::Type::Symbol));
    SExpression *val1 = new SExpression(new Atom(1L));
    env.set(var1, val1);

    // Test retrieval of existing variables
    SExpression *retrieved1 = env.lookup(var1);
    if (retrieved1 != nullptr && retrieved1->getType() == SExpression::Type::Atom &&
        retrieved1->getAtom()->getType() == Atom::Type::Long &&
        retrieved1->getAtom()->getLong() == 1L) {
        Logger::log("PASS: Set and lookup 1 variable", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Failed to retrieve first set variable", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Another variable
    SExpression *var2 = new SExpression(new Atom("y", Atom::Type::Symbol));
    SExpression *val2 = new SExpression(new Atom("Hello", Atom::Type::String));
    env.set(var2, val2);

    SExpression *retrieved2 = env.lookup(var2);
    if (retrieved2 != nullptr && retrieved2->getType() == SExpression::Type::Atom &&
        retrieved2->getAtom()->getType() == Atom::Type::String &&
        retrieved2->getAtom()->getString() == "Hello") {
        Logger::log("PASS: Set and lookup 2 variable", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Failed to retrieve 2nd variable 'y'.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Set 2nd var to another value
    val2 = new SExpression(new Atom("Test", Atom::Type::String));
    env.set(var2, val2);

    retrieved2 = env.lookup(var2);
    if (retrieved2 != nullptr && retrieved2->getType() == SExpression::Type::Atom &&
        retrieved2->getAtom()->getType() == Atom::Type::String &&
        retrieved2->getAtom()->getString() == "Test") {
        Logger::log("PASS: Update Environment variable 'y'", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Update Environment variable 'y'", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Test retrieval of non-existing variable
    SExpression *var3 = new SExpression(new Atom("z", Atom::Type::Symbol));
    SExpression *retrieved3 = env.lookup(var3);
    // Should return itself
    if (LogicalFunction::eq(retrieved3, var3)) {
        Logger::log("PASS: lookup non-existing variable returns itself", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: lookup non-existing variable did not return itself", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Test retrieval with invalid atom type
    SExpression *invalidVar = new SExpression(new Atom(42L)); // Not a symbol
    SExpression *retrievedInvalid = env.lookup(invalidVar);
    if (LogicalFunction::eq(retrievedInvalid, invalidVar)) {
        Logger::log("PASS: lookup invalid variable returns itself", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: lookup invalid variable did not return itself", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Test retrieval with non-atom SExpression
    SExpression *consSym = new SExpression(new Atom("a", Atom::Type::Symbol));
    ConsCell *cons = new ConsCell(var1, var2);
    SExpression *consExpr = new SExpression(cons);
    env.set(consSym, consExpr);
    SExpression *retrievedCons = env.lookup(consSym);
    if (retrievedCons != nullptr && retrievedCons->getType() == SExpression::Type::ConsCell) {
        Logger::log("PASS: Set and lookup ConsCell", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Set and lookup ConsCell", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Test lookup nil
    SExpression *nilSym = new SExpression();
    SExpression *retrievedNil = env.lookup(nilSym);
    if (LogicalFunction::eq(retrievedNil, nilSym)) {
        Logger::log("PASS: lookup nil returns itself", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: lookup nil did not return itself", Logger::ERROR);
        fails++;
        pass = false;
    }

    return pass;
}