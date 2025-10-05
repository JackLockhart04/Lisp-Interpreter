#pragma once

#include "../types/atom.h"
#include "../types/s_expression.h"
#include "type_checker.h"
#include "../util/logger.h"
#include "logical_function.h"

class NumberFunction {
public:
    // Arithmetic
	static SExpression* add(const SExpression* expr1, const SExpression* expr2);
    static SExpression* sub(const SExpression* expr1, const SExpression* expr2);
    static SExpression* mul(const SExpression* expr1, const SExpression* expr2);
    static SExpression* div(const SExpression* expr1, const SExpression* expr2);
    static SExpression* mod(const SExpression* expr1, const SExpression* expr2);

    // Comparison
    static SExpression* lt(const SExpression* expr1, const SExpression* expr2);
    static SExpression* gt(const SExpression* expr1, const SExpression* expr2);
    static SExpression* lte(const SExpression* expr1, const SExpression* expr2);
    static SExpression* gte(const SExpression* expr1, const SExpression* expr2);
};