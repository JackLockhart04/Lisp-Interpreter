#include "types/atom.h"
#include "types/cons.h"
#include "types/s_expression.h"

class SexpTester {
public:
    static void runTests(int &passes, int &fails);
private:
    static bool testGetType(int &passes, int &fails);
    static bool testGetAtom(int &passes, int &fails);
    static bool testGetCons(int &passes, int &fails);
};