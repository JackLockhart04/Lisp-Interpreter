#include "types/s_expression.h"
#include "types/atom.h"
#include "types/cons.h"

class ConsTester {
public:
    static void runTests(int &passes, int &fails);
private:
    static bool testCadr(int &passes, int &fails);
    static bool testToVector(int &passes, int &fails);
};