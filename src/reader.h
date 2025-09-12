#pragma once

#include "util/logger/logger.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

class Reader {
public:
    // If filename is empty, read from stdin; otherwise, read from file
    Reader(const std::string& filename = "");
    char next(); // Returns next character as int, or EOF
    char peek(); // Returns next character without consuming it
    bool hasFile() const { return useFile; }
    bool hasError() const { return hasErrorFlag; }
    std::string getErrorMessage() const { return errorMessage; }

private:
    std::string filename;
    std::ifstream fileStream;
    std::istringstream line;
    bool useFile;
    bool hasErrorFlag;
    std::string errorMessage;

    void loadNextLine();
};
