#include "reader_test.h"
#include "reader.h"

bool ReaderTester::runTest(int &passes, int &fails) {
    // Test reading from a file and comparing to expected output
    bool pass = true;
    std::string fileName = "../tests/reader/test_cases.txt";
    std::ifstream file(fileName);
    if (!file.is_open()) {
        Logger::log("Could not open file: " + fileName, Logger::ERROR);
        return false;
    }
    Reader reader(fileName);
    int pos = 0;
    while (true) {
        int fileCh;
        // Skip carriage returns in file
        do {
            fileCh = file.get();
        } while (fileCh == 13); // 13 is '\r'
        char readerCh = reader.next();
        if (fileCh == EOF && readerCh == '\n') break;
        if (fileCh != readerCh) {
            Logger::log(
                "Reader char '" + std::string(1, readerCh) +
                "' does not match file char '" + std::string(1, fileCh) +
                "' at position " + std::to_string(pos),
                Logger::DEBUG
            );
            pass = false;
            break;
        }
        ++pos;
    }
    file.close();
    if (pass) {
        Logger::log("PASS: Reader tests passed.", Logger::INFO);
        passes++;
        return true;
    } else {
        Logger::log("FAIL: Reader output does NOT match file contents", Logger::ERROR);
        fails++;
        return false;
    }
}
