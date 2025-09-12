#include "core/type_checker.h"
#include "types/atom.h"
#include "types/s_expression.h"

class TypeCheckerTester {
public:
    TypeCheckerTester();
    static bool runTest(int &passes, int &fails);
private:
    static bool testIsNil(int &passes, int &fails);
    static bool testIsNumber(int &passes, int &fails);
    static bool testIsSymbol(int &passes, int &fails);
    static bool testIsString(int &passes, int &fails);
    static bool testIsList(int &passes, int &fails);
};