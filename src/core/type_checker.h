#pragma once
#include "../types/s_expression.h"

class TypeChecker {
public:
	static bool isNil(const SExpression* expr);
	// Returns true if the expression is a number (integer or double)
	static bool isNumber(const SExpression* expr);

	// Returns true if the expression is a symbol
	static bool isSymbol(const SExpression* expr);
    static bool isString(const SExpression* expr);

	// Returns true if the expression is a list (cons cell)
	static bool isList(const SExpression* expr);
};