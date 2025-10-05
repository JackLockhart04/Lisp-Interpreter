#pragma once

#include "types/s_expression.h"
#include "types/atom.h"
#include "util/logger.h"
#include "core/environment.h"

#include "conditional.h"
#include "number_function.h"

SExpression* eval(SExpression* expr, Environment* env);
SExpression* evalAtom(SExpression* expr, Environment* env);
SExpression* evalList(SExpression* expr, Environment* env);
SExpression* evalPredefinedFunction(SExpression* expr, Environment* env);
SExpression* evalLambda(SExpression* expr, Environment* env);