#pragma once

#include "types/s_expression.h"
#include "types/cons.h"
#include "types/atom.h"
#include "core/logical_function.h"

#include <vector>

class Environment{
public:
    Environment();
    Environment(SExpression* symbols, SExpression* values);
    Environment(Environment *other, SExpression* symbols, SExpression* values);
    ~Environment();

    SExpression* symbols;
    SExpression* values;

    void set(SExpression* symbol, SExpression* value);
    SExpression* lookup(SExpression* symbol);

    SExpression* getSymbols() { return symbols; }
    SExpression* getValues() { return values; }
};