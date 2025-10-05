#pragma once

#include "types/atom.h"
#include "types/s_expression.h"
#include "type_checker.h"
#include "util/logger.h"

class LogicalFunction {
public:
    static SExpression* eq(const SExpression* expr1, const SExpression* expr2);
    static SExpression* logical_not(const SExpression* expr1);
    static bool isTrue(const SExpression* expr);
};