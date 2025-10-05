#include "number_function.h"

SExpression* NumberFunction::add(const SExpression* expr1, const SExpression* expr2) {
    // Ensure both a number
    bool isNumber1 = TypeChecker::isNumber(expr1);
    bool isNumber2 = TypeChecker::isNumber(expr2);
    if(!isNumber1 || !isNumber2) {
        // Logger::log("Both arguments to add must be numbers.", Logger::ERROR);
        // Error atom
        Atom *errorAtom = new Atom("Not numbers", Atom::Type::String);
        return new SExpression(errorAtom); // Return error atom on error
    }

    // Ensure both Long or both Double
    bool bothLong = expr1->getAtom()->getType() == Atom::Type::Long &&
            expr2->getAtom()->getType() == Atom::Type::Long;
    bool bothDouble = expr1->getAtom()->getType() == Atom::Type::Double &&
            expr2->getAtom()->getType() == Atom::Type::Double;
    if (!bothLong && !bothDouble) {
        // Error atom
        Atom *errorAtom = new Atom("Not same type", Atom::Type::String);
        return new SExpression(errorAtom); // Return error atom on error
    }

    // If 1 or both are double, result is double
    if (bothDouble) {
        double val1 = expr1->getAtom()->getDouble();
        double val2 = expr2->getAtom()->getDouble();
        return new SExpression(new Atom(val1 + val2));
    } else {
        long val1 = expr1->getAtom()->getLong();
        long val2 = expr2->getAtom()->getLong();
        return new SExpression(new Atom(val1 + val2));
    }

    return new SExpression(); // Default to nil (Shouldnt reach here)
}

SExpression* NumberFunction::sub(const SExpression* expr1, const SExpression* expr2) {
    // Ensure both a number
    bool isNumber1 = TypeChecker::isNumber(expr1);
    bool isNumber2 = TypeChecker::isNumber(expr2);
    if (!isNumber1 || !isNumber2) {
        Atom *errorAtom = new Atom("Not numbers", Atom::Type::String);
        return new SExpression(errorAtom); // Return error atom on error
    }

    // Ensure both Long or both Double
    bool bothLong = expr1->getAtom()->getType() == Atom::Type::Long &&
            expr2->getAtom()->getType() == Atom::Type::Long;
    bool bothDouble = expr1->getAtom()->getType() == Atom::Type::Double &&
            expr2->getAtom()->getType() == Atom::Type::Double;
    if (!bothLong && !bothDouble) {
        // Error atom
        Atom *errorAtom = new Atom("Not same type", Atom::Type::String);
        return new SExpression(errorAtom); // Return error atom on error
    }

    // If 1 or both are double, result is double
    if (bothDouble) {
        double val1 = expr1->getAtom()->getDouble();
        double val2 = expr2->getAtom()->getDouble();
        return new SExpression(new Atom(val1 - val2));
    } else {
        long val1 = expr1->getAtom()->getLong();
        long val2 = expr2->getAtom()->getLong();
        return new SExpression(new Atom(val1 - val2));
    }

    return new SExpression(); // Default to nil (Shouldnt reach here)
}

SExpression* NumberFunction::mul(const SExpression* expr1, const SExpression* expr2) {
    // Ensure both numbers
    bool isNumber1 = TypeChecker::isNumber(expr1);
    bool isNumber2 = TypeChecker::isNumber(expr2);
    if (!isNumber1 || !isNumber2) {
        // Error atom
        Atom *errorAtom = new Atom("Not numbers", Atom::Type::String);
        return new SExpression(errorAtom); // Return error atom on error
    }

    // Both same type
    bool bothLong = expr1->getAtom()->getType() == Atom::Type::Long &&
            expr2->getAtom()->getType() == Atom::Type::Long;
    bool bothDouble = expr1->getAtom()->getType() == Atom::Type::Double &&
            expr2->getAtom()->getType() == Atom::Type::Double;
    if (!bothLong && !bothDouble) {
        // Error atom
        Atom *errorAtom = new Atom("Not same type", Atom::Type::String);
        return new SExpression(errorAtom); // Return error atom on error
    }

    // If 1 or both are double, result is double
    if (bothDouble) {
        double val1 = expr1->getAtom()->getDouble();
        double val2 = expr2->getAtom()->getDouble();
        return new SExpression(new Atom(val1 * val2));
    } else {
        long val1 = expr1->getAtom()->getLong();
        long val2 = expr2->getAtom()->getLong();
        return new SExpression(new Atom(val1 * val2));
    }

    return new SExpression(); // Default to nil (Shouldnt reach here)
}

SExpression* NumberFunction::div(const SExpression* expr1, const SExpression* expr2) {
    // Ensure both Long or Double
    bool isNumber1 = TypeChecker::isNumber(expr1);
    bool isNumber2 = TypeChecker::isNumber(expr2);
    if (!isNumber1 || !isNumber2) {
        // Logger::log("Both arguments to div must be numbers.", Logger::ERROR);
        // Error atom
        Atom *errorAtom = new Atom("Not numbers", Atom::Type::String);
        return new SExpression(errorAtom); // Return error atom on error
    }

    // Both same type
    bool bothLong = expr1->getAtom()->getType() == Atom::Type::Long &&
            expr2->getAtom()->getType() == Atom::Type::Long;
    bool bothDouble = expr1->getAtom()->getType() == Atom::Type::Double &&
            expr2->getAtom()->getType() == Atom::Type::Double;
    if (!bothLong && !bothDouble) {
        // Error atom
        Atom *errorAtom = new Atom("Not same type", Atom::Type::String);
        return new SExpression(errorAtom); // Return error atom on error
    }

    // Check for division by zero
    if ((bothLong && expr2->getAtom()->getLong() == 0) ||
            (bothDouble && expr2->getAtom()->getDouble() == 0.0)) {
        // Logger::log("Division by zero.", Logger::ERROR);
        Atom *errorAtom = new Atom("Division by zero", Atom::Type::String);
        return new SExpression(errorAtom); // Return error atom on division by zero
    }

    // Divide
    if (bothDouble) {
        double val1 = expr1->getAtom()->getDouble();
        double val2 = expr2->getAtom()->getDouble();
        return new SExpression(new Atom(val1 / val2));
    } else {
        long val1 = expr1->getAtom()->getLong();
        long val2 = expr2->getAtom()->getLong();
        return new SExpression(new Atom(val1 / val2));
    }

    return new SExpression(); // Default to nil (Shouldnt reach here)
}

SExpression* NumberFunction::mod(const SExpression* expr1, const SExpression* expr2) {
    // Ensure both Long
    bool isNumber1 = TypeChecker::isNumber(expr1);
    bool isNumber2 = TypeChecker::isNumber(expr2);
    if (!isNumber1 || !isNumber2) {
        // Logger::log("Both arguments to mod must be numbers.", Logger::ERROR);
        // Error atom
        Atom *errorAtom = new Atom("Not numbers", Atom::Type::String);
        return new SExpression(errorAtom); // Return error atom on error
    }

    Atom* atom1 = expr1->getAtom();
    Atom* atom2 = expr2->getAtom();

    if (atom1->getType() != Atom::Type::Long || atom2->getType() != Atom::Type::Long) {
        // Logger::log("Both arguments to mod must be integers.", Logger::ERROR);
        // Error atom
        Atom *errorAtom = new Atom("Not integers", Atom::Type::String);
        return new SExpression(errorAtom); // Return error atom on error
    }

    // Check for division by zero
    if (atom2->getLong() == 0) {
        // Logger::log("Modulus by zero.", Logger::ERROR);
        Atom *errorAtom = new Atom("Modulus by zero", Atom::Type::String);
        return new SExpression(errorAtom); // Return error atom on modulus by zero
    }

    long val1 = atom1->getLong();
    long val2 = atom2->getLong();
    SExpression *result = new SExpression(new Atom(val1 % val2));

    return result;
}

// Comparison functions
SExpression* NumberFunction::lt(const SExpression* expr1, const SExpression* expr2) {
    // Ensure both Long or Double
    bool isNumber1 = TypeChecker::isNumber(expr1);
    bool isNumber2 = TypeChecker::isNumber(expr2);
    if (!isNumber1 || !isNumber2) {
        // Logger::log("Both arguments to lt must be numbers.", Logger::ERROR);
        // Error atom
        Atom *errorAtom = new Atom("Not numbers", Atom::Type::String);
        return new SExpression(errorAtom); // Return error atom on error
    }

    // Ensure same type
    bool bothLong = expr1->getAtom()->getType() == Atom::Type::Long &&
            expr2->getAtom()->getType() == Atom::Type::Long;
    bool bothDouble = expr1->getAtom()->getType() == Atom::Type::Double &&
            expr2->getAtom()->getType() == Atom::Type::Double;
    if (!bothLong && !bothDouble) {
        // Error atom
        Atom *errorAtom = new Atom("Not same type", Atom::Type::String);
        return new SExpression(errorAtom); // Return error atom on error
    }

    Atom* atom1 = expr1->getAtom();
    Atom* atom2 = expr2->getAtom();

    bool comparisonResult = false;

    // If 1 or both are double, compare as double
    if (bothDouble) {
        double val1 = atom1->getDouble();
        double val2 = atom2->getDouble();
        comparisonResult = val1 < val2;
    } else {
        long val1 = atom1->getLong();
        long val2 = atom2->getLong();
        comparisonResult = val1 < val2;
    }

    if(comparisonResult) {
        return new SExpression(new Atom("t", Atom::Type::Symbol));
    } else {
        return new SExpression(); // Nil
    }
}

SExpression* NumberFunction::gt(const SExpression* expr1, const SExpression* expr2) {
    // Ensure both Long or Double
    bool isNumber1 = TypeChecker::isNumber(expr1);
    bool isNumber2 = TypeChecker::isNumber(expr2);
    if (!isNumber1 || !isNumber2) {
        // Logger::log("Both arguments to gt must be numbers.", Logger::ERROR);
        // Error atom
        Atom *errorAtom = new Atom("Not numbers", Atom::Type::String);
        return new SExpression(errorAtom); // Return error atom on error
    }

    // Ensure same type
    bool bothLong = expr1->getAtom()->getType() == Atom::Type::Long &&
            expr2->getAtom()->getType() == Atom::Type::Long;
    bool bothDouble = expr1->getAtom()->getType() == Atom::Type::Double &&
            expr2->getAtom()->getType() == Atom::Type::Double;
    if (!bothLong && !bothDouble) {
        // Error atom
        Atom *errorAtom = new Atom("Not same type", Atom::Type::String);
        return new SExpression(errorAtom); // Return error atom on error
    }

    Atom* atom1 = expr1->getAtom();
    Atom* atom2 = expr2->getAtom();

    bool comparisonResult = false;

    // If 1 or both are double, compare as double
    if (bothDouble) {
        double val1 = atom1->getDouble();
        double val2 = atom2->getDouble();
        comparisonResult = val1 > val2;
    } else {
        long val1 = atom1->getLong();
        long val2 = atom2->getLong();
        comparisonResult = val1 > val2;
    }

    if(comparisonResult) {
        return new SExpression(new Atom("t", Atom::Type::Symbol));
    } else {
        return new SExpression(new Atom()); // Nil
    }
}

SExpression* NumberFunction::lte(const SExpression* expr1, const SExpression* expr2) {
    // Ensure both Long or both Double
    bool isNumber1 = TypeChecker::isNumber(expr1);
    bool isNumber2 = TypeChecker::isNumber(expr2);
    if (!isNumber1 || !isNumber2) {
        // Logger::log("Both arguments to lte must be numbers.", Logger::ERROR);
        // Error atom
        Atom *errorAtom = new Atom("Not numbers", Atom::Type::String);
        return new SExpression(errorAtom); // Return error atom on error
    }

    // Ensure same type
    bool bothLong = expr1->getAtom()->getType() == Atom::Type::Long &&
            expr2->getAtom()->getType() == Atom::Type::Long;
    bool bothDouble = expr1->getAtom()->getType() == Atom::Type::Double &&
            expr2->getAtom()->getType() == Atom::Type::Double;
    if (!bothLong && !bothDouble) {
        // Error atom
        Atom *errorAtom = new Atom("Not same type", Atom::Type::String);
        return new SExpression(errorAtom); // Return error atom on error
    }

    SExpression *ltResult = lt(expr1, expr2);
    SExpression *eqResult = LogicalFunction::eq(expr1, expr2);
    // If ltResult is true or eqResult is true, return true
    if ((ltResult->getType() == SExpression::Type::Atom &&
            ltResult->getAtom()->getType() == Atom::Type::Symbol &&
            ltResult->getAtom()->getSymbol() == "t") ||
        (eqResult->getType() == SExpression::Type::Atom &&
            eqResult->getAtom()->getType() == Atom::Type::Symbol &&
            eqResult->getAtom()->getSymbol() == "t")) {
        return new SExpression(new Atom("t", Atom::Type::Symbol));
    } else {
        return new SExpression(); // Nil
    }
}

SExpression* NumberFunction::gte(const SExpression* expr1, const SExpression* expr2) {
    // Ensure both Long or both Double
    bool isNumber1 = TypeChecker::isNumber(expr1);
    bool isNumber2 = TypeChecker::isNumber(expr2);
    if (!isNumber1 || !isNumber2) {
        // Logger::log("Both arguments to gte must be numbers.", Logger::ERROR);
        // Error atom
        Atom *errorAtom = new Atom("Not numbers", Atom::Type::String);
        return new SExpression(errorAtom); // Return error atom on error
    }

    // Ensure same type
    bool bothLong = expr1->getAtom()->getType() == Atom::Type::Long &&
            expr2->getAtom()->getType() == Atom::Type::Long;
    bool bothDouble = expr1->getAtom()->getType() == Atom::Type::Double &&
            expr2->getAtom()->getType() == Atom::Type::Double;
    if (!bothLong && !bothDouble) {
        // Error atom
        Atom *errorAtom = new Atom("Not same type", Atom::Type::String);
        return new SExpression(errorAtom); // Return error atom on error
    }

    SExpression *gtResult = gt(expr1, expr2);
    SExpression *eqResult = LogicalFunction::eq(expr1, expr2);
    // If gtResult is true or eqResult is true, return true
    if ((gtResult->getType() == SExpression::Type::Atom &&
            gtResult->getAtom()->getType() == Atom::Type::Symbol &&
            gtResult->getAtom()->getSymbol() == "t") || 
        (eqResult->getType() == SExpression::Type::Atom &&
            eqResult->getAtom()->getType() == Atom::Type::Symbol &&
            eqResult->getAtom()->getSymbol() == "t")) {
        return new SExpression(new Atom("t", Atom::Type::Symbol));
    } else {
        return new SExpression(); // Nil
    }
}