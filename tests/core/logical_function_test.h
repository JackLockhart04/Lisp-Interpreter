#pragma once

#include "core/logical_function.h"
#include "types/atom.h"
#include "types/cons.h"
#include "types/s_expression.h"
#include "util/logger.h"

class LogicalFunctionTester {
public:
    static bool runTest(int &passes, int &fails);
private:
    // Equality tests
    static bool testEq(int &passes, int &fails);
    static bool testNot(int &passes, int &fails);
};