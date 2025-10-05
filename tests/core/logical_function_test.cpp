#include "logical_function_test.h"

bool LogicalFunctionTester::runTest(int &passes, int &fails) {
    bool allPassed = true;
    // Equality tests
    allPassed &= testEq(passes, fails);
    allPassed &= testNot(passes, fails);

    return allPassed;
}

// Equality tests
bool LogicalFunctionTester::testEq(int &passes, int &fails) {
    bool pass = true;
    // Test cases for eq
    // Long equality
    SExpression expr1(new Atom(5L));
    SExpression expr2(new Atom(5L));
    SExpression *result = LogicalFunction::eq(&expr1, &expr2);
    if (LogicalFunction::isTrue(result)) {
        Logger::log("PASS: Long equality is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Long equality is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Long inequality
    SExpression expr3(new Atom(5L));
    SExpression expr4(new Atom(10L));
    result = LogicalFunction::eq(&expr3, &expr4);
    if (!LogicalFunction::isTrue(result)) {
        Logger::log("PASS: Long inequality is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Long inequality is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Double equality
    SExpression expr5(new Atom(5.5));
    SExpression expr6(new Atom(5.5));
    result = LogicalFunction::eq(&expr5, &expr6);
    if (LogicalFunction::isTrue(result)) {
        Logger::log("PASS: Double equality is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Double equality is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Double inequality
    SExpression expr7(new Atom(5.5));
    SExpression expr8(new Atom(4.5));
    result = LogicalFunction::eq(&expr7, &expr8);
    if (!LogicalFunction::isTrue(result)) {
        Logger::log("PASS: Double inequality is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Double inequality is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Symbol equality
    SExpression expr9(new Atom("sym", Atom::Type::Symbol));
    SExpression expr10(new Atom("sym", Atom::Type::Symbol));
    result = LogicalFunction::eq(&expr9, &expr10);
    if (LogicalFunction::isTrue(result)) {
        Logger::log("PASS: Symbol equality is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Symbol equality is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Symbol inequality
    SExpression expr11(new Atom("sym1", Atom::Type::Symbol));
    SExpression expr12(new Atom("sym2", Atom::Type::Symbol));
    result = LogicalFunction::eq(&expr11, &expr12);
    if (!LogicalFunction::isTrue(result)) {
        Logger::log("PASS: Symbol inequality is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Symbol inequality is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // String equality
    SExpression expr13(new Atom("hello", Atom::Type::String));
    SExpression expr14(new Atom("hello", Atom::Type::String));
    result = LogicalFunction::eq(&expr13, &expr14);
    if (LogicalFunction::isTrue(result)) {
        Logger::log("PASS: String equality is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: String equality is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // String inequality
    SExpression expr15(new Atom("hello", Atom::Type::String));
    SExpression expr16(new Atom("world", Atom::Type::String));
    result = LogicalFunction::eq(&expr15, &expr16);
    if (!LogicalFunction::isTrue(result)) {
        Logger::log("PASS: String inequality is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: String inequality is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Nil equality
    SExpression expr17(new Atom());
    SExpression expr18(new Atom());
    result = LogicalFunction::eq(&expr17, &expr18);
    if (LogicalFunction::isTrue(result)) {
        Logger::log("PASS: Nil equality is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Nil equality is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Different types
    SExpression expr19(new Atom(5L));
    SExpression expr20(new Atom(5.0));
    result = LogicalFunction::eq(&expr19, &expr20);
    if (!LogicalFunction::isTrue(result)) {
        Logger::log("PASS: Different type inequality is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Different type inequality is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Different types with nil
    SExpression expr21(new Atom(5L));
    SExpression expr22(new Atom());
    result = LogicalFunction::eq(&expr21, &expr22);
    if (!LogicalFunction::isTrue(result)) {
        Logger::log("PASS: Different type with nil inequality is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Different type with nil inequality is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    return pass;
}

bool LogicalFunctionTester::testNot(int &passes, int &fails) {
    bool pass = true;
  
    // Test cases for not
    // Not nil (false)
    SExpression nilExpr(new Atom());
    SExpression *result = LogicalFunction::logical_not(&nilExpr);
    if (LogicalFunction::isTrue(result)) {
        Logger::log("PASS: Not nil -> t is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Not nil -> t is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Non-nil (true)
    SExpression nonNilExpr(new Atom(5L));
    result = LogicalFunction::logical_not(&nonNilExpr);
    if (!LogicalFunction::isTrue(result)) {
        Logger::log("PASS: Non-nil -> nil is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Non-nil -> nil is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Not non-atom (error)
    // Cons cell
    ConsCell *consCell = new ConsCell(new SExpression(new Atom(1L)), new SExpression(new Atom()));
    SExpression nonAtomExpr(consCell);
    result = LogicalFunction::logical_not(&nonAtomExpr);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not an atom") {
        Logger::log("PASS: Not non-atom is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Not non-atom is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    return pass;
}