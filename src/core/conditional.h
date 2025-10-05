#pragma once

#include "types/s_expression.h"
#include "types/atom.h"
#include "types/cons.h"
#include "core/eval.h"
#include "core/environment.h"
#include "logical_function.h"

class Conditional {
public:
    static SExpression* and_(SExpression* expr1, SExpression* expr2, Environment* env);
    static SExpression* or_(SExpression* expr1, SExpression* expr2, Environment* env);
    static SExpression* if_(SExpression* expr1, SExpression* expr2, SExpression* expr3, Environment* env);
    static SExpression* cond(SExpression* expr, Environment* env);
};  