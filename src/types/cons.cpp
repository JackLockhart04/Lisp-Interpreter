#include "cons.h"
#include "s_expression.h"

#include <iostream>
#include <memory>

ConsCell::ConsCell(SExpression* car, SExpression* cdr) {
    this->car = car;
    this->cdr = cdr;
}

ConsCell::~ConsCell() {}

SExpression& ConsCell::getCar() {
    return *car;
}

SExpression& ConsCell::getCdr() {
    return *cdr;
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