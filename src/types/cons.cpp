#include "cons.h"
#include "s_expression.h"

#include <iostream>
#include <memory>

ConsCell::ConsCell(SExpression* car, SExpression* cdr) {
    this->car = car;
    this->cdr = cdr;
}

// Copy
ConsCell::ConsCell(const ConsCell& other) {
    // Deep copy car and cdr
    if (other.car) {
        car = new SExpression(*other.car); // Calls SExpression copy constructor
    } else {
        car = nullptr;
    }
    if (other.cdr) {
        cdr = new SExpression(*other.cdr); // Calls SExpression copy constructor
    } else {
        cdr = nullptr;
    }
}

ConsCell::~ConsCell() {}

SExpression* ConsCell::getCar() {
    return car;
}

SExpression* ConsCell::getCdr() {
    return cdr;
}

SExpression* ConsCell::getCadr() {
    // Ensure cdr is a cons cell
    if (cdr->getType() != SExpression::Type::ConsCell) {
        // Return nil
        SExpression *nil = new SExpression();
        return nil;
    }
    return cdr->getCons()->getCar();
}

SExpression* ConsCell::getCaddr() {
    // Ensure cdr is a cons cell
    if (cdr->getType() != SExpression::Type::ConsCell) {
        // Return nil
        SExpression *nil = new SExpression();
        return nil;
    }
    SExpression *second = cdr->getCons()->getCdr();
    // Ensure second is a cons cell
    if (second->getType() != SExpression::Type::ConsCell) {
        // Return nil
        SExpression *nil = new SExpression();
        return nil;
    }
    return second->getCons()->getCar();
}

int ConsCell::getLength(){
    int length = 0;
    ConsCell* current = this;
    while (true) {
        length++;
        // If cdr is another cons cell, continue traversing the list
        if (current->cdr && current->cdr->getType() == SExpression::Type::ConsCell) {
            current = current->cdr->getCons();
        } else {
            break;
        }
    }
    return length;
}

// Helpers
void ConsCell::print() const {
    std::cout << "(";
    if (car) car->print();
    std::cout << " ";
    if (cdr) cdr->print();
    std::cout << ")";
}

std::vector<SExpression*> ConsCell::toVector() {
    std::vector<SExpression*> result;
    ConsCell* current = this;
    while (true) {
        // Add the car (head) of the current cons cell to the result
        if (current->car) {
            result.push_back(current->car);
        }
        // If cdr is another cons cell, continue traversing the list
        if (current->cdr && current->cdr->getType() == SExpression::Type::ConsCell) {
            current = current->cdr->getCons();
        } else {
            // Add the final cdr (tail)
            result.push_back(current->cdr);
            break;
        }
    }
    return result;
}