#include "type_checker.h"
#include "../types/atom.h"

bool TypeChecker::isNil(const SExpression* expr) {
	if (expr->getType() != SExpression::Type::Atom) return false;
	Atom* atom = expr->getAtom();
	return atom->getType() == Atom::Type::Nil;
}

bool TypeChecker::isNumber(const SExpression* expr) {
	if (expr->getType() != SExpression::Type::Atom) return false;
	Atom* atom = expr->getAtom();
	return atom->getType() == Atom::Type::Long || atom->getType() == Atom::Type::Double;
}

bool TypeChecker::isSymbol(const SExpression* expr) {
	if (expr->getType() != SExpression::Type::Atom) return false;
	Atom* atom = expr->getAtom();
	return atom->getType() == Atom::Type::Symbol;
}

bool TypeChecker::isString(const SExpression* expr) {
    if (expr->getType() != SExpression::Type::Atom) return false;
    Atom* atom = expr->getAtom();
    return atom->getType() == Atom::Type::String;
}

bool TypeChecker::isList(const SExpression* expr) {
	bool isListBool = expr->getType() == SExpression::Type::ConsCell;
	bool isNilBool = isNil(expr);
	return isListBool || isNilBool;
}

