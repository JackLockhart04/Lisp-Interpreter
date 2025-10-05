#pragma once

#include "core/environment.h"
#include "types/atom.h"
#include "types/cons.h"
#include "types/s_expression.h"
#include "core/logical_function.h"
#include "util/logger.h"

class EnvironmentTester {
public:
    static bool runTests(int &passes, int &fails);

private:
    static bool testLookup(int &passes, int &fails);
};