#pragma once

#include "util/logger.h"

#include <string>

class Atom {
public:
    enum class Type {
        Long,
        Double,
        Symbol,
        String,
        Nil,
        END_OF_FILE
    };

    // Constructors for each type
    Atom(const Atom& other); // Copy
    Atom(Type type = Type::Nil); // For Nil type
    Atom(long longValue);
    Atom(double doubleValue);
    Atom(const std::string& value, Type type); // For Symbol or String
    ~Atom();

    Type getType() const;
    long getLong() const;
    double getDouble() const;
    std::string getSymbol() const;
    std::string getString() const;
    void print() const;

private:
    Type type;
    long longValue;
    double doubleValue;
    std::string stringValue;
};


