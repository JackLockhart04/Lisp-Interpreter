#include "environment.h"

Environment::Environment() {
    symbols = new SExpression(); // Nil
    values = new SExpression();  // Nil
}

Environment::Environment(SExpression* symbols, SExpression* values) {
    // Copy the provided lists with deep copy
    this->symbols = new SExpression(*symbols);
    this->values = new SExpression(*values);
}

Environment::Environment(Environment *other, SExpression* symbols, SExpression* values) {
    // Logger::log("Creating new environment with parent", Logger::INFO);
    // Set current symbols as old environment
    if(other->getSymbols()->getType() != SExpression::Type::ConsCell) {
        // Logger::log("Parent environment has no symbols", Logger::WARNING);
        this->symbols = new SExpression(); // Nil
        this->values = new SExpression();  // Nil
    } else {
        this->symbols = new SExpression(*other->getSymbols());
        this->values = new SExpression(*other->getValues());
    }

    // Add new symbols and values to front of lists
    std::vector<SExpression*> newSymbols = symbols->getCons()->toVector();
    std::vector<SExpression*> newValues = values->getCons()->toVector();
    for(int i = newSymbols.size() - 1; i >= 0; i--) {
        ConsCell *newSymCons = new ConsCell(newSymbols[i], this->symbols);
        this->symbols = new SExpression(newSymCons);
    }
    for(int i = newValues.size() - 1; i >= 0; i--) {
        ConsCell *newValCons = new ConsCell(newValues[i], this->values);
        this->values = new SExpression(newValCons);
    }

    // Logger::log("New environment created", Logger::INFO);
}

Environment::~Environment() {
    delete symbols;
    delete values;
}

void Environment::set(SExpression* symbol, SExpression* value) {
    // Ensure symbol is an atom of type symbol
    if (symbol->getType() != SExpression::Type::Atom ||
        symbol->getAtom()->getType() != Atom::Type::Symbol) {
        // Logger::log("Invalid symbol type. Expected a symbol.", Logger::ERROR);
        return;
    }

    // Add symbol-value pair to environment
    ConsCell *newSymbols = new ConsCell(symbol, symbols);
    symbols = new SExpression(newSymbols);
    ConsCell *newValues = new ConsCell(value, values);
    values = new SExpression(newValues);
}

SExpression* Environment::lookup(SExpression* symbol) {
    // Logger::log("Looking up symbol in environment", Logger::INFO);
    // Ensure symbol is an atom of type symbol
    if (symbol->getType() != SExpression::Type::Atom ||
        symbol->getAtom()->getType() != Atom::Type::Symbol) {
        // Logger::log("Invalid symbol type. Expected a symbol.", Logger::ERROR);
        return symbol; // Return itself
    }

    // Find the value associated with the symbol
    SExpression *symList = symbols;
    SExpression *valList = values;

    while(symList->getType() == SExpression::Type::ConsCell) {
        ConsCell *symCons = symList->getCons();
        ConsCell *valCons = valList->getCons();

        // Check if the current symbol matches
        SExpression *currentSym = symCons->getCar();
        SExpression *result = LogicalFunction::eq(symbol, currentSym);
        // If matches
        if (LogicalFunction::isTrue(result)) {
            // Found the symbol, return the associated value
            // Logger::log("Symbol found in environment", Logger::INFO);
            return valCons->getCar();
        }

        symList = symCons->getCdr();
        valList = valCons->getCdr();
    }

    // Symbol not found, return itself
    // Logger::log("Symbol not found in environment", Logger::WARNING);
    return symbol;
}
