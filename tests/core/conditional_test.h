#include "core/conditional.h"

#include "types/s_expression.h"
#include "core/environment.h"
#include "core/logical_function.h"

class ConditionalTester {
public:
    static bool runTests(int &passes, int &fails);
    static bool testAnd(int &passes, int &fails);
    static bool testOr(int &passes, int &fails);
    static bool testIf(int &passes, int &fails);
    static bool testCond(int &passes, int &fails);
};