#include "atom.h"

#include <stdexcept>

// Copy constructor
Atom::Atom(const Atom& other) {
    Logger::log("Copying Atom of type: " + std::to_string(static_cast<int>(other.type)), Logger::DEBUG);
    type = other.type;
    longValue = other.longValue;
    doubleValue = other.doubleValue;
    stringValue = other.stringValue;
}

// Type only
Atom::Atom(Type type) {
    Logger::log("Creating Atom of type: " + std::to_string(static_cast<int>(type)), Logger::DEBUG);

    this->type = type;
    longValue = 0;
    doubleValue = 0.0;
    stringValue = "";
}

// Long constructor
Atom::Atom(long longValue) {
    Logger::log("Creating Atom of type: Long with value: " + std::to_string(longValue), Logger::DEBUG);
    type = Type::Long;
    this->longValue = longValue;
    doubleValue = 0.0;
    stringValue = "";
}

// Double constructor
Atom::Atom(double doubleValue) {
    Logger::log("Creating Atom of type: Double with value: " + std::to_string(doubleValue), Logger::DEBUG);
    type = Type::Double;
    longValue = 0;
    this->doubleValue = doubleValue;
    stringValue = "";
}

// Symbol or String constructor
Atom::Atom(const std::string& value, Type type) {
    Logger::log("Creating Atom of type: " + std::to_string(static_cast<int>(type)) + " with value: " + value, Logger::DEBUG);
    if (type != Type::Symbol && type != Type::String) {
        throw std::invalid_argument("Type must be Symbol or String for this constructor");
    }
    this->type = type;
    longValue = 0;
    doubleValue = 0.0;
    stringValue = value;
}

Atom::~Atom() {}

Atom::Type Atom::getType() const {
    return type;
}

long Atom::getLong() const {
    if (type != Type::Long) {
        Logger::log("Attempted to get long from non-long atom", Logger::WARNING);
        return 0;
    }
    return longValue;
}

double Atom::getDouble() const {
    if (type != Type::Double) {
        Logger::log("Attempted to get double from non-double atom", Logger::WARNING);
        return 0.0;
    }
    return doubleValue;
}

std::string Atom::getSymbol() const {
    if (type != Type::Symbol) {
        Logger::log("Attempted to get symbol from non-symbol atom", Logger::WARNING);
        return "";
    }
    return stringValue;
}

void Atom::print() const {
    switch (type) {
        case Type::Long:
            printf("%d", longValue);
            break;
        case Type::Double:
            printf("%f", doubleValue);
            break;
        case Type::Symbol:
            printf("%s", stringValue.c_str());
            break;
        case Type::String:
            printf("\"%s\"", stringValue.c_str());
            break;
        case Type::Nil:
            printf("()");
            break;
    }
}

std::string Atom::getString() const {
    if (type != Type::String){
        Logger::log("Attempted to get string from non-string atom", Logger::WARNING);
        throw std::logic_error("Not a string atom");
    }
    return stringValue;
}
