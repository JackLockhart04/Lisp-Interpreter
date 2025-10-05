#include "logical_function.h"

SExpression* LogicalFunction::eq(const SExpression* expr1, const SExpression* expr2) {
    // Check if both are atoms
    if (!(expr1->getType() == SExpression::Type::Atom && expr2->getType() == SExpression::Type::Atom)) {
        // Logger::log("Both arguments to eq must be atoms.", Logger::ERROR);
        // Error atom
        Atom *errorAtom = new Atom("Not atoms", Atom::Type::String);
        return new SExpression(errorAtom); // Return error atom on error
    }

    Atom* atom1 = expr1->getAtom();
    Atom* atom2 = expr2->getAtom();

    // If types differ, return false
    if (atom1->getType() != atom2->getType()) {
        return new SExpression(new Atom()); // false
    }

    Atom *trueAtom = new Atom("t", Atom::Type::Symbol); // true
    Atom *falseAtom = new Atom(); // false
    // Compare based on type
    Atom::Type type1 = atom1->getType();
    switch (type1) {
        case Atom::Type::Long: {
            bool result = (atom1->getLong() == atom2->getLong());
            SExpression *res = new SExpression(result ? trueAtom : falseAtom);
            return res;
        }
        case Atom::Type::Double: {
            bool result = (atom1->getDouble() == atom2->getDouble());
            SExpression *res = new SExpression(result ? trueAtom : falseAtom);
            return res;
        }
        case Atom::Type::Symbol: {
            bool result = (atom1->getSymbol() == atom2->getSymbol());
            SExpression *res = new SExpression(result ? trueAtom : falseAtom);
            return res;
        }
        case Atom::Type::String: {
            bool result = (atom1->getString() == atom2->getString());
            SExpression *res = new SExpression(result ? trueAtom : falseAtom);
            return res;
        }
        case Atom::Type::Nil: {
            // Both are nil
            return new SExpression(trueAtom);
        }
        default:
            // Logger::log("Unsupported atom type for eq.", Logger::ERROR);
            // Error atom
            Atom *errorAtom = new Atom("Unsupported type", Atom::Type::String);
            return new SExpression(errorAtom); // Return error atom on error
    }
}

SExpression* LogicalFunction::logical_not(const SExpression* expr1) {
    // Check if the argument is an atom
    if (expr1->getType() != SExpression::Type::Atom) {
        // Error atom
        Atom *errorAtom = new Atom("Not an atom", Atom::Type::String);
        return new SExpression(errorAtom); // Return error atom on error
    }

    Atom* atom1 = expr1->getAtom();

    // If atom is nil, return true
    if (atom1->getType() == Atom::Type::Nil) {
        return new SExpression(new Atom("t", Atom::Type::Symbol)); // true
    } else {
        return new SExpression(new Atom()); // false
    }
}

bool LogicalFunction::isTrue(const SExpression* expr) {
    // Cons are true
    if (expr->getType() == SExpression::Type::ConsCell) {
        return true;
    }
    // Atoms are true if not nil
    Atom* atom = expr->getAtom();
    bool isTrue = (atom->getType() != Atom::Type::Nil);
    return isTrue;
}