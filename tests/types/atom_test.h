#include "types/atom.h"

class AtomTester {
public:
    static void runTests(int &passes, int &fails);
private:
    static bool testGetValue(int &passes, int &fails);
    static bool testGetType(int &passes, int &fails);
};