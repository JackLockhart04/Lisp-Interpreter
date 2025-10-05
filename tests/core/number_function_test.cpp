#include "number_function_test.h"

bool NumberFunctionTester::runTest(int &passes, int &fails) {
    bool allPassed = true;
    // Arithmetic tests
    allPassed &= testAdd(passes, fails);
    allPassed &= testSub(passes, fails);
    allPassed &= testMul(passes, fails);
    allPassed &= testDiv(passes, fails);
    allPassed &= testMod(passes, fails);

    // Comparison tests
    allPassed &= testLt(passes, fails);
    allPassed &= testLte(passes, fails);
    allPassed &= testGt(passes, fails);
    allPassed &= testGte(passes, fails);

    return allPassed;
}

// Arithmetic tests
bool NumberFunctionTester::testAdd(int &passes, int &fails) {
    bool pass = true;
    // Test cases for addition
    SExpression *expr1 = new SExpression(new Atom(5L));
    SExpression *expr2 = new SExpression(new Atom(10L));
    SExpression *result = NumberFunction::add(expr1, expr2);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::Long &&
            result->getAtom()->getLong() == 15L) {
        Logger::log("PASS: Long addition is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Long addition is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Double addition
    SExpression *expr3 = new SExpression(new Atom(5.5));
    SExpression *expr4 = new SExpression(new Atom(4.5));
    result = NumberFunction::add(expr3, expr4);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::Double &&
            result->getAtom()->getDouble() == 10.0) {
        Logger::log("PASS: Double addition is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Double addition is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Mixed addition (Shouldnt work)
    SExpression *expr5 = new SExpression(new Atom(5L));
    SExpression *expr6 = new SExpression(new Atom(4.5));
    result = NumberFunction::add(expr5, expr6);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not same type") {
        Logger::log("PASS: Mixed addition correctly not allowed.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Mixed addition is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Add a long and nil, (Should return atom with string "Not numbers")
    SExpression *expr7 = new SExpression(new Atom(5L));
    SExpression *expr8 = new SExpression(new Atom(Atom::Type::Nil));
    result = NumberFunction::add(expr7, expr8);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not numbers") {
        Logger::log("PASS: Addition with nil is correctly an error.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Addition with nil is incorrect, expected an error.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Add a string and a long, (Should return atom with string "Not numbers")
    SExpression *expr9 = new SExpression(new Atom("Hello", Atom::Type::String));
    SExpression *expr10 = new SExpression(new Atom(5L));
    result = NumberFunction::add(expr9, expr10);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not numbers") {
        Logger::log("PASS: Addition with string is correctly an error.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Addition with string is incorrect, expected an error.", Logger::ERROR);
        fails++;
        pass = false;
    }

    return pass;
}

bool NumberFunctionTester::testSub(int &passes, int &fails) {
    bool pass = true;
    // Test cases for subtraction
    // Longs
    SExpression *expr1 = new SExpression(new Atom(5L));
    SExpression *expr2 = new SExpression(new Atom(10L));
    SExpression *result = NumberFunction::sub(expr1, expr2);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::Long &&
            result->getAtom()->getLong() == -5L) {
        Logger::log("PASS: Long subtraction is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Long subtraction is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Doubles
    SExpression *expr3 = new SExpression(new Atom(5.5));
    SExpression *expr4 = new SExpression(new Atom(4.5));
    result = NumberFunction::sub(expr3, expr4);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::Double &&
            result->getAtom()->getDouble() == 1.0) {
        Logger::log("PASS: Double subtraction is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Double subtraction is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Long - Double (Shouldnt work)
    SExpression *expr5 = new SExpression(new Atom(5L));
    SExpression *expr6 = new SExpression(new Atom(4.5));
    result = NumberFunction::sub(expr5, expr6);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not same type") {
        Logger::log("PASS: Mixed subtraction is correctly not allowed.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Mixed subtraction is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Add a long and nil, (Should return atom with string "Not numbers")
    SExpression *expr7 = new SExpression(new Atom(5L));
    SExpression *expr8 = new SExpression(new Atom(Atom::Type::Nil));
    result = NumberFunction::sub(expr7, expr8);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not numbers") {
        Logger::log("PASS: Subtraction with nil is correctly an error.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Subtraction with nil is incorrect, expected an error.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Add a string and a long, (Should return atom with string "Not numbers")
    SExpression *expr9 = new SExpression(new Atom("Hello", Atom::Type::String));
    SExpression *expr10 = new SExpression(new Atom(5L));
    result = NumberFunction::sub(expr9, expr10);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not numbers") {
        Logger::log("PASS: Subtraction with string is correctly an error.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Subtraction with string is incorrect, expected an error.", Logger::ERROR);
        fails++;
        pass = false;
    }

    return pass;
}

bool NumberFunctionTester::testMul(int &passes, int &fails) {
    bool pass = true;
    // Test cases for multiplication
    // Long
    SExpression *expr1 = new SExpression(new Atom(5L));
    SExpression *expr2 = new SExpression(new Atom(10L));
    SExpression *result = NumberFunction::mul(expr1, expr2);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::Long &&
            result->getAtom()->getLong() == 50L) {
        Logger::log("PASS: Long multiplication is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Long multiplication is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Double
    SExpression *expr3 = new SExpression(new Atom(5.5));
    SExpression *expr4 = new SExpression(new Atom(4.5));
    result = NumberFunction::mul(expr3, expr4);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::Double &&
            result->getAtom()->getDouble() == 24.75) {
        Logger::log("PASS: Double multiplication is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Double multiplication is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Mixed (Not allowed)
    SExpression *expr5 = new SExpression(new Atom(5L));
    SExpression *expr6 = new SExpression(new Atom(4.5));
    result = NumberFunction::mul(expr5, expr6);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not same type") {
        Logger::log("PASS: Mixed multiplication is correctly not allowed.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Mixed multiplication is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Add a long and nil, (Should return atom with string "Not numbers")
    SExpression *expr7 = new SExpression(new Atom(5L));
    SExpression *expr8 = new SExpression(new Atom(Atom::Type::Nil));
    result = NumberFunction::mul(expr7, expr8);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not numbers") {
        Logger::log("PASS: Multiplication with nil is correctly an error.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Multiplication with nil is incorrect, expected an error.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Add a string and a long, (Should return atom with string "Not numbers")
    SExpression *expr9 = new SExpression(new Atom("Hello", Atom::Type::String));
    SExpression *expr10 = new SExpression(new Atom(5L));
    result = NumberFunction::mul(expr9, expr10);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not numbers") {
        Logger::log("PASS: Multiplication with string is correctly an error.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Multiplication with string is incorrect, expected an error.", Logger::ERROR);
        fails++;
        pass = false;
    }

    return pass;
}

bool NumberFunctionTester::testDiv(int &passes, int &fails) {
    bool pass = true;
    // Test cases for division
    // Long
    SExpression *expr1 = new SExpression(new Atom(10L));
    SExpression *expr2 = new SExpression(new Atom(5L));
    SExpression *result = NumberFunction::div(expr1, expr2);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::Long &&
            result->getAtom()->getLong() == 2L) {
        Logger::log("PASS: Long division is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Long division is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Doubles
    SExpression *expr3 = new SExpression(new Atom(5.5));
    SExpression *expr4 = new SExpression(new Atom(1.1));
    result = NumberFunction::div(expr3, expr4);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::Double &&
            result->getAtom()->getDouble() == 5.0) {
        Logger::log("PASS: Double division is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Double division is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Divide a long by a double (Shouldnt work)
    SExpression *expr5 = new SExpression(new Atom(10L));
    SExpression *expr6 = new SExpression(new Atom(4.0));
    result = NumberFunction::div(expr5, expr6);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not same type") {
        Logger::log("PASS: Mixed division (long/double) is correctly not allowed.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Mixed division (long/double) is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Divide a double by a long
    SExpression *expr7 = new SExpression(new Atom(9.0));
    SExpression *expr8 = new SExpression(new Atom(3L));
    result = NumberFunction::div(expr7, expr8);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not same type") {
        Logger::log("PASS: Mixed division (double/long) is correctly not allowed.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Mixed division (double/long) is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Divide by zero (long)
    SExpression *expr9 = new SExpression(new Atom(10L));
    SExpression *expr10 = new SExpression(new Atom(0L));
    result = NumberFunction::div(expr9, expr10);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Division by zero") {
        Logger::log("PASS: Division by zero (long) is correctly an error.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Division by zero (long) is incorrect, expected an error.", Logger::ERROR);
        fails++;
        pass = false;
    } 

    // Divide by zero (double)
    SExpression *expr11 = new SExpression(new Atom(10.0));
    SExpression *expr12 = new SExpression(new Atom(0.0));
    result = NumberFunction::div(expr11, expr12);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Division by zero") {
        Logger::log("PASS: Division by zero (double) is correctly an error.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Division by zero (double) is incorrect, expected an error.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Divide a long and nil, (Should return atom with string "Not numbers")
    SExpression *expr13 = new SExpression(new Atom(5L));
    SExpression *expr14 = new SExpression(new Atom(Atom::Type::Nil));
    result = NumberFunction::div(expr13, expr14);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not numbers") {
        Logger::log("PASS: Division with nil is correctly an error.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Division with nil is incorrect, expected an error.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Divide a string and a long, (Should return atom with string "Not numbers")
    SExpression *expr15 = new SExpression(new Atom("Hello", Atom::Type::String));
    SExpression *expr16 = new SExpression(new Atom(5L));
    result = NumberFunction::div(expr15, expr16);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not numbers") {
        Logger::log("PASS: Division with string is correctly an error.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Division with string is incorrect, expected an error.", Logger::ERROR);
        fails++;
        pass = false;
    }

    return pass;
}

bool NumberFunctionTester::testMod(int &passes, int &fails) {
    bool pass = true;
    // Test cases for modulus
    SExpression *expr1 = new SExpression(new Atom(5L));
    SExpression *expr2 = new SExpression(new Atom(10L));
    SExpression *result = NumberFunction::mod(expr1, expr2);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::Long &&
            result->getAtom()->getLong() == 5L) {
        Logger::log("PASS: Long modulus is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Long modulus is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Modulus by zero (long)
    SExpression *expr3 = new SExpression(new Atom(10L));
    SExpression *expr4 = new SExpression(new Atom(0L));
    result = NumberFunction::mod(expr3, expr4);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Modulus by zero") {
        Logger::log("PASS: Modulus by zero is correctly an error.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Modulus by zero is incorrect, expected an error.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Modulus a long and double, (Should return atom with string "Not integers")
    SExpression *expr5 = new SExpression(new Atom(5L));
    SExpression *expr6 = new SExpression(new Atom(2.5));
    result = NumberFunction::mod(expr5, expr6);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not integers") {
        Logger::log("PASS: Modulus with double is correctly an error.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Modulus with double is incorrect, expected an error.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Modulus a long and nil, (Should return atom with string "Not numbers")
    SExpression *expr7 = new SExpression(new Atom(5L));
    SExpression *expr8 = new SExpression(new Atom(Atom::Type::Nil));
    result = NumberFunction::mod(expr7, expr8);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not numbers") {
        Logger::log("PASS: Modulus with nil is correctly an error.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Modulus with nil is incorrect, expected an error.", Logger::ERROR);
        fails++;
        pass = false;
    }

    return pass;
}

// Comparison functions tests
bool NumberFunctionTester::testLt(int &passes, int &fails) {
    bool pass = true;
    // Test cases for less than
    // Long less than
    SExpression *expr1 = new SExpression(new Atom(1L));
    SExpression *expr2 = new SExpression(new Atom(2L));
    SExpression *result = NumberFunction::lt(expr1, expr2);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::Symbol &&
            result->getAtom()->getSymbol() == "t") {
        Logger::log("PASS: Long less than is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Long less than is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Long not less than
    SExpression *expr3 = new SExpression(new Atom(2L));
    SExpression *expr4 = new SExpression(new Atom(1L));
    result = NumberFunction::lt(expr3, expr4);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::Nil) {
        Logger::log("PASS: Long not less than is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Long not less than is incorrect.", Logger::ERROR);
        fails++;
        pass = false; 
    }

    // Double less than
    SExpression *expr5 = new SExpression(new Atom(1.1));
    SExpression *expr6 = new SExpression(new Atom(2.1));
    result = NumberFunction::lt(expr5, expr6);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::Symbol &&
            result->getAtom()->getSymbol() == "t") {
        Logger::log("PASS: Double less than is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Double less than is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }
    // Double not less than
    SExpression *expr7 = new SExpression(new Atom(2.1));
    SExpression *expr8 = new SExpression(new Atom(1.1));
    result = NumberFunction::lt(expr7, expr8);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::Nil) {
        Logger::log("PASS: Double not less than is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Double not less than is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Mixed less than (long < double)
    SExpression *expr9 = new SExpression(new Atom(1L));
    SExpression *expr10 = new SExpression(new Atom(2.1));
    result = NumberFunction::lt(expr9, expr10);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not same type") {
        Logger::log("PASS: Mixed less than (long < double) is correctly an error.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Mixed less than (long < double) is incorrect, expected an error.", Logger::ERROR);
        fails++;
        pass = false;
    } 

    // Mixed not less than (long < double)
    SExpression *expr11 = new SExpression(new Atom(2L));
    SExpression *expr12 = new SExpression(new Atom(1.1));
    result = NumberFunction::lt(expr11, expr12);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not same type") {
        Logger::log("PASS: Mixed not less than (long < double) is correctly an error.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Mixed not less than (long < double) is incorrect, expected an error.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Using a string (Should return atom with string "Not numbers")
    SExpression *expr13 = new SExpression(new Atom("Hello", Atom::Type::String));
    SExpression *expr14 = new SExpression(new Atom(1L));
    result = NumberFunction::lt(expr13, expr14);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not numbers") {
        Logger::log("PASS: Less than with string is correctly an error.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Less than with string is incorrect, expected an error.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Using nil (Should return atom with string "Not numbers")
    SExpression *expr15 = new SExpression(new Atom(Atom::Type::Nil));
    SExpression *expr16 = new SExpression(new Atom(1L));
    result = NumberFunction::lt(expr15, expr16);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not numbers") {
        Logger::log("PASS: Less than with nil is correctly an error.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Less than with nil is incorrect, expected an error.", Logger::ERROR);
        fails++;
        pass = false;
    }

    return pass;
}

bool NumberFunctionTester::testLte(int &passes, int &fails) {
    bool pass = true;
    // Test cases for less than or equal
    // Long less than
    SExpression *expr1 = new SExpression(new Atom(1L));
    SExpression *expr2 = new SExpression(new Atom(2L));
    SExpression *result = NumberFunction::lte(expr1, expr2);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::Symbol &&
            result->getAtom()->getSymbol() == "t") {
        Logger::log("PASS: Long less/equal than is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Long less/equal than is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Long not less than
    SExpression *expr3 = new SExpression(new Atom(2L));
    SExpression *expr4 = new SExpression(new Atom(1L));
    result = NumberFunction::lte(expr3, expr4);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::Nil) {
        Logger::log("PASS: Long not less/equal than is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Long not less/equal than is incorrect.", Logger::ERROR);
        fails++;
        pass = false; 
    }

    // Long equal
    SExpression *expr5 = new SExpression(new Atom(2L));
    SExpression *expr6 = new SExpression(new Atom(2L));
    result = NumberFunction::lte(expr5, expr6);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::Symbol &&
            result->getAtom()->getSymbol() == "t") {
        Logger::log("PASS: Long less than/equal is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Long less than/equal is incorrect.", Logger::ERROR);
        fails++;
        pass = false; 
    }

    // Double less than
    SExpression *expr7 = new SExpression(new Atom(1.1));
    SExpression *expr8 = new SExpression(new Atom(2.1));
    result = NumberFunction::lte(expr7, expr8);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::Symbol &&
            result->getAtom()->getSymbol() == "t") {
        Logger::log("PASS: Double less than/equal is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Double less than/equal is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }
    // Double not less than
    SExpression *expr9 = new SExpression(new Atom(2.1));
    SExpression *expr10 = new SExpression(new Atom(1.1));
    result = NumberFunction::lte(expr9, expr10);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::Nil) {
        Logger::log("PASS: Double not less than/equal is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Double not less than/equal is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Double equal
    // FIXME sometimes fails due to precision issues with floating point comparison
    SExpression *expr11 = new SExpression(new Atom(2.1));
    SExpression *expr12 = new SExpression(new Atom(2.1));
    result = NumberFunction::lte(expr11, expr12);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::Symbol &&
            result->getAtom()->getSymbol() == "t") {
        Logger::log("PASS: Double less than/equal is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Double less than/equal is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Mixed less than (long < double)
    SExpression *expr13 = new SExpression(new Atom(1L));
    SExpression *expr14 = new SExpression(new Atom(2.1));
    result = NumberFunction::lte(expr13, expr14);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not same type") {
        Logger::log("PASS: Mixed less than/equal (long < double) is correctly an error.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Mixed less than/equal (long < double) is incorrect, expected an error.", Logger::ERROR);
        fails++;
        pass = false;
    } 

    // Mixed not less than (long < double)
    SExpression *expr15 = new SExpression(new Atom(2L));
    SExpression *expr16 = new SExpression(new Atom(1.1));
    result = NumberFunction::lte(expr15, expr16);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not same type") {
        Logger::log("PASS: Mixed not less/equal than (long < double) is correctly an error.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Mixed not less/equal than (long < double) is incorrect, expected an error.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Using a string (Should return atom with string "Not numbers")
    SExpression *expr17 = new SExpression(new Atom("Hello", Atom::Type::String));
    SExpression *expr18 = new SExpression(new Atom(1L));
    result = NumberFunction::lte(expr17, expr18);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not numbers") {
        Logger::log("PASS: Less than/equal with string is correctly an error.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Less than/equal with string is incorrect, expected an error.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Using nil (Should return atom with string "Not numbers")
    SExpression *expr19 = new SExpression(new Atom(Atom::Type::Nil));
    SExpression *expr20 = new SExpression(new Atom(1L));
    result = NumberFunction::lte(expr19, expr20);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not numbers") {
        Logger::log("PASS: Less than/equal with nil is correctly an error.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Less than/equal with nil is incorrect, expected an error.", Logger::ERROR);
        fails++;
        pass = false;
    }

    return pass;
}

bool NumberFunctionTester::testGt(int &passes, int &fails) {
       bool pass = true;
    // Long greater than
    SExpression *expr1 = new SExpression(new Atom(2L));
    SExpression *expr2 = new SExpression(new Atom(1L));
    SExpression *result = NumberFunction::gt(expr1, expr2);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::Symbol &&
            result->getAtom()->getSymbol() == "t") {
        Logger::log("PASS: Long greater than is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Long greater than is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Long not greater than
    SExpression *expr3 = new SExpression(new Atom(1L));
    SExpression *expr4 = new SExpression(new Atom(2L));
    result = NumberFunction::gt(expr3, expr4);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::Nil) {
        Logger::log("PASS: Long not greater than is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Long not greater than is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Double greater than
    SExpression *expr5 = new SExpression(new Atom(2.1));
    SExpression *expr6 = new SExpression(new Atom(1.1));
    result = NumberFunction::gt(expr5, expr6);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::Symbol &&
            result->getAtom()->getSymbol() == "t") {
        Logger::log("PASS: Double greater than is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Double greater than is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }
    // Double not greater than
    SExpression *expr7 = new SExpression(new Atom(1.1));
    SExpression *expr8 = new SExpression(new Atom(2.1));
    result = NumberFunction::gt(expr7, expr8);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::Nil) {
        Logger::log("PASS: Double not greater than is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Double not greater than is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Mixed greater than (long > double)
    SExpression *expr9 = new SExpression(new Atom(2L));
    SExpression *expr10 = new SExpression(new Atom(1.1));
    result = NumberFunction::gt(expr9, expr10);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not same type") {
        Logger::log("PASS: Mixed greater than (long > double) is correctly an error.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Mixed greater than (long > double) is incorrect, expected an error.", Logger::ERROR);
        fails++;
        pass = false;
    } 

    // Mixed not greater than (long > double)
    SExpression *expr11 = new SExpression(new Atom(1L));
    SExpression *expr12 = new SExpression(new Atom(2.1));
    result = NumberFunction::gt(expr11, expr12);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not same type") {
        Logger::log("PASS: Mixed not greater than (long > double) is correctly an error.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Mixed not greater than (long > double) is incorrect, expected an error.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Using a string (Should return atom with string "Not numbers")
    SExpression *expr13 = new SExpression(new Atom("Hello", Atom::Type::String));
    SExpression *expr14 = new SExpression(new Atom(1L));
    result = NumberFunction::gt(expr13, expr14);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not numbers") {
        Logger::log("PASS: Greater than with string is correctly an error.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Greater than with string is incorrect, expected an error.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Using nil (Should return atom with string "Not numbers")
    SExpression *expr15 = new SExpression(new Atom(Atom::Type::Nil));
    SExpression *expr16 = new SExpression(new Atom(1L));
    result = NumberFunction::gt(expr15, expr16);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not numbers") {
        Logger::log("PASS: Greater than with nil is correctly an error.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Greater than with nil is incorrect, expected an error.", Logger::ERROR);
        fails++;
        pass = false;
    }

    return pass;
}

bool NumberFunctionTester::testGte(int &passes, int &fails) {
    bool pass = true;
    // Long greater or equal
    SExpression *expr1 = new SExpression(new Atom(2L));
    SExpression *expr2 = new SExpression(new Atom(1L));
    SExpression *result = NumberFunction::gte(expr1, expr2);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::Symbol &&
            result->getAtom()->getSymbol() == "t") {
        Logger::log("PASS: Long greater/equal than is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Long greater/equal than is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Long not greater or equal
    SExpression *expr3 = new SExpression(new Atom(1L));
    SExpression *expr4 = new SExpression(new Atom(2L));
    result = NumberFunction::gte(expr3, expr4);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::Nil) {
        Logger::log("PASS: Long not greater/equal than is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Long not greater/equal than is incorrect.", Logger::ERROR);
        fails++;
        pass = false; 
    }

    // Long equal
    SExpression *expr5 = new SExpression(new Atom(2L));
    SExpression *expr6 = new SExpression(new Atom(2L));
    result = NumberFunction::gte(expr5, expr6);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::Symbol &&
            result->getAtom()->getSymbol() == "t") {
        Logger::log("PASS: Long greater/equal is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Long greater/equal is incorrect.", Logger::ERROR);
        fails++;
        pass = false; 
    }

    // Double greater or equal
    SExpression *expr7 = new SExpression(new Atom(2.1));
    SExpression *expr8 = new SExpression(new Atom(1.1));
    result = NumberFunction::gte(expr7, expr8);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::Symbol &&
            result->getAtom()->getSymbol() == "t") {
        Logger::log("PASS: Double greater/equal is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Double greater/equal is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }
    // Double not greater or equal
    SExpression *expr9 = new SExpression(new Atom(1.1));
    SExpression *expr10 = new SExpression(new Atom(2.1));
    result = NumberFunction::gte(expr9, expr10);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::Nil) {
        Logger::log("PASS: Double not greater/equal is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Double not greater/equal is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Double equal
    SExpression *expr11 = new SExpression(new Atom(2.1));
    SExpression *expr12 = new SExpression(new Atom(2.1));
    result = NumberFunction::gte(expr11, expr12);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::Symbol &&
            result->getAtom()->getSymbol() == "t") {
        Logger::log("PASS: Double greater/equal is correct.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Double greater/equal is incorrect.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Mixed greater or equal (long > double)
    SExpression *expr13 = new SExpression(new Atom(2L));
    SExpression *expr14 = new SExpression(new Atom(1.1));
    result = NumberFunction::gte(expr13, expr14);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not same type") {
        Logger::log("PASS: Mixed greater/equal (long > double) is correctly an error.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Mixed greater/equal (long > double) is incorrect, expected an error.", Logger::ERROR);
        fails++;
        pass = false;
    } 

    // Mixed not greater or equal (long > double)
    SExpression *expr15 = new SExpression(new Atom(1L));
    SExpression *expr16 = new SExpression(new Atom(2.1));
    result = NumberFunction::gte(expr15, expr16);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not same type") {
        Logger::log("PASS: Mixed not greater/equal (long > double) is correctly an error.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Mixed not greater/equal (long > double) is incorrect, expected an error.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Using a string (Should return atom with string "Not numbers")
    SExpression *expr17 = new SExpression(new Atom("Hello", Atom::Type::String));
    SExpression *expr18 = new SExpression(new Atom(1L));
    result = NumberFunction::gte(expr17, expr18);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not numbers") {
        Logger::log("PASS: Greater/equal with string is correctly an error.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Greater/equal with string is incorrect, expected an error.", Logger::ERROR);
        fails++;
        pass = false;
    }

    // Using nil (Should return atom with string "Not numbers")
    SExpression *expr19 = new SExpression(new Atom(Atom::Type::Nil));
    SExpression *expr20 = new SExpression(new Atom(1L));
    result = NumberFunction::gte(expr19, expr20);
    if (result->getType() == SExpression::Type::Atom &&
            result->getAtom()->getType() == Atom::Type::String &&
            result->getAtom()->getString() == "Not numbers") {
        Logger::log("PASS: Greater/equal with nil is correctly an error.", Logger::INFO);
        passes++;
    } else {
        Logger::log("FAIL: Greater/equal with nil is incorrect, expected an error.", Logger::ERROR);
        fails++;
        pass = false;
    }

    return pass;
}