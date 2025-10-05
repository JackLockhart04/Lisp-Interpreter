#pragma once

#include "core/number_function.h"
#include "types/atom.h"
#include "types/cons.h"
#include "types/s_expression.h"
#include "util/logger.h"

class NumberFunctionTester {
public:
    static bool runTest(int &passes, int &fails);
private:
    // Arithmetic tests
    static bool testAdd(int &passes, int &fails);
    static bool testSub(int &passes, int &fails);
    static bool testMul(int &passes, int &fails);
    static bool testDiv(int &passes, int &fails);
    static bool testMod(int &passes, int &fails);

    // Comparison tests
    static bool testLt(int &passes, int &fails);
    static bool testLte(int &passes, int &fails);
    static bool testGt(int &passes, int &fails);
    static bool testGte(int &passes, int &fails);
};