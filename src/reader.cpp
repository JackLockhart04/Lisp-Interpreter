#include "reader.h"

Reader::Reader(const std::string& filename) {
    this->filename = filename;
    useFile = !filename.empty();
    if (useFile) {
        // Open file
        Logger::log("Initializing Reader with filename: '" + filename + "'", Logger::DEBUG);
        fileStream.open(filename);
        // If couldn't open file
        if (!fileStream.is_open()) {
            hasErrorFlag = true;
            errorMessage = "Couldn't open file '" + filename + "'";
            Logger::log(errorMessage, Logger::ERROR);
            useFile = false;
            return;
        // File opened successfully
        } else {
            hasErrorFlag = false;
            errorMessage.clear();
        }
    } else {
        Logger::log("Initializing Reader with standard input.", Logger::DEBUG);
    }

    // Get first line
    loadNextLine();
}

// Currently inefficient but works
char Reader::next() {
    // If line is empty, get next line
    if (line.eof() || line.peek() == EOF) {
        loadNextLine();
        // If still empty, return EOF
        if (line.str().empty() || line.peek() == EOF) {
            return EOF;
        }
    }

    // Get next character from line
    char ch = line.get();    
    while (ch == '\r') { // skip carriage returns
        ch = line.get();
        if (ch == EOF){
            return EOF;
        }
    }
    return ch;
}

char Reader::peek() {   
    if (line.eof() || line.peek() == EOF) {
        loadNextLine();
    }
    if (line.str().empty() || line.peek() == EOF) {
        return EOF;
    }
    char ch = line.peek();
    return ch;
}

void Reader::loadNextLine() {
    // Logger::log("Loading next line...", Logger::DEBUG);
    std::cout << "> " << std::flush;
    std::string lineStr;
    if (useFile) {
        if (std::getline(fileStream, lineStr)) {
            lineStr += '\n';
            line.str(lineStr);
            line.clear(); // Clear eof and fail bits
        } else {
            line.str(""); // No more lines
            line.clear(); // Clear eof and fail bits
        }
    } else {
        if (std::getline(std::cin, lineStr)) {
            lineStr += '\n';
            line.str(lineStr);
            line.clear(); // Clear eof and fail bits
        } else {
            line.str(""); // No more lines
            line.clear(); // Clear eof and fail bits
        }
    }

    // Logger::log("Loaded line: '" + lineStr + "'", Logger::DEBUG);
}
