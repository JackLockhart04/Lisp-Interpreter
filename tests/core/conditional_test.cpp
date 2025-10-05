#include "conditional_test.h"

bool ConditionalTester::runTests(int &passes, int &fails) {
    bool allPassed = true;
    allPassed &= testAnd(passes, fails);
    allPassed &= testOr(passes, fails);
    allPassed &= testIf(passes, fails);
    allPassed &= testCond(passes, fails);

    return allPassed;
}

bool ConditionalTester::testAnd(int &passes, int &fails) {
    bool pass = true;
    Environment *env = new Environment();

    // True and True
    SExpression *expr1 = new SExpression(new Atom(1L));
    SExpression *expr2 = new SExpression(new Atom(2L));
    SExpression *result = Conditional::and_(expr1, expr2, env);
    SExpression *eq = LogicalFunction::eq(result, expr2);
    if (LogicalFunction::isTrue(eq)) {
        Logger::log("PASS: and_ true/true returns second expr.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: and_ true/true failed.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // False and True
    SExpression *nilExpr = new SExpression();
    result = Conditional::and_(nilExpr, expr2, env);
    eq = LogicalFunction::eq(result, nilExpr);
    if (LogicalFunction::isTrue(eq)) {
        Logger::log("PASS: and_ false/true returns false.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: and_ false/true failed.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // True and False
    result = Conditional::and_(expr1, nilExpr, env);
    eq = LogicalFunction::eq(result, nilExpr);
    if (LogicalFunction::isTrue(eq)) {
        Logger::log("PASS: and_ true/false returns false.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: and_ true/false failed.", Logger::ERROR);
        fails++;
        pass = false;
    }

    return pass;
}

bool ConditionalTester::testOr(int &passes, int &fails) {
    bool pass = true;
    Environment *env = new Environment();

    // True or True
    SExpression *expr1 = new SExpression(new Atom(1L));
    SExpression *expr2 = new SExpression(new Atom(2L));
    SExpression *result = Conditional::or_(expr1, expr2, env);
    SExpression *truthy = new SExpression(new Atom("t", Atom::Type::Symbol));
    SExpression *eq = LogicalFunction::eq(result, truthy);
    if (LogicalFunction::isTrue(eq)) {
        Logger::log("PASS: or_ true/true returns first expr.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: or_ true/true failed.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // False or True
    SExpression *nilExpr = new SExpression();
    result = Conditional::or_(nilExpr, expr2, env);
    eq = LogicalFunction::eq(result, expr2);
    if (LogicalFunction::isTrue(eq)) {
        Logger::log("PASS: or_ false/true returns true.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: or_ false/true failed.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // True or False
    result = Conditional::or_(expr1, nilExpr, env);
    eq = LogicalFunction::eq(result, truthy);
    if (LogicalFunction::isTrue(eq)) {
        Logger::log("PASS: or_ true/false returns true.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: or_ true/false failed.", Logger::ERROR);
        fails++;
        pass = false;
    }

    return pass;
}

bool ConditionalTester::testIf(int &passes, int &fails) {
    bool pass = true;
    Environment *env = new Environment();

    // If True
    SExpression *condition = new SExpression(new Atom(1L));
    SExpression *thenExpr = new SExpression(new Atom(2L));
    SExpression *elseExpr = new SExpression(new Atom(3L));
    SExpression *result = Conditional::if_(condition, thenExpr, elseExpr, env);
    SExpression *eq = LogicalFunction::eq(result, thenExpr);
    if (LogicalFunction::isTrue(eq)) {
        Logger::log("PASS: if_ true returns then expr.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: if_ true failed.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // If False
    SExpression *nilExpr = new SExpression();
    result = Conditional::if_(nilExpr, thenExpr, elseExpr, env);
    eq = LogicalFunction::eq(result, elseExpr);
    if (LogicalFunction::isTrue(eq)) {
        Logger::log("PASS: if_ false returns else expr.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: if_ false failed.", Logger::ERROR);
        fails++;
        pass = false;
    }

    return pass;
}

bool ConditionalTester::testCond(int &passes, int &fails) {
    bool pass = true;
    Environment *env = new Environment();

    // (cond ((nil 1) (t 2)))
    SExpression *nilExpr = new SExpression();
    SExpression *falseVal = new SExpression(new Atom(1L));
    SExpression *tExpr = new SExpression(new Atom("t", Atom::Type::Symbol));
    SExpression *trueVal = new SExpression(new Atom(2L));

    // (nil 1)
    SExpression *falseCase = new SExpression(new ConsCell(nilExpr, new SExpression(new ConsCell(falseVal, nilExpr))));
    // (t 2)
    SExpression *truthyCase = new SExpression(new ConsCell(tExpr, new SExpression(new ConsCell(trueVal, nilExpr))));

    // False case followed by true case (should return 2)
    SExpression *cases = new SExpression(new ConsCell(falseCase, new SExpression(new ConsCell(truthyCase, nilExpr))));
    SExpression *result = Conditional::cond(cases, env);
    SExpression *expected = trueVal;
    SExpression *eq = LogicalFunction::eq(result, expected);
    if (LogicalFunction::isTrue(eq)) {
        Logger::log("PASS: cond returns correct value for first true case.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: cond did not return correct value for first true case.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // True case first (should return 1)
    cases = new SExpression(new ConsCell(truthyCase, new SExpression(new ConsCell(falseCase, nilExpr))));
    result = Conditional::cond(cases, env);
    expected = trueVal;
    eq = LogicalFunction::eq(result, expected);
    if (LogicalFunction::isTrue(eq)) {
        Logger::log("PASS: cond returns correct value for second true case.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: cond did not return correct value for second true case.", Logger::ERROR);
        fails++;
        pass = false;
    }

    return pass;
}