#include "s_expression.h"
#include "atom.h"
#include "cons.h"

#include <iostream>
#include <memory>
#include <stdexcept>

SExpression::SExpression(Atom* atom) {
    type = Type::Atom;
    atomPtr = atom;
    consPtr = nullptr;
}

SExpression::SExpression(ConsCell* cons) {
    type = Type::ConsCell;
    atomPtr = nullptr;
    consPtr = cons;
}

SExpression::~SExpression() {}

SExpression::Type SExpression::getType() const {
    return type;
}

Atom* SExpression::getAtom() const {
    if (type != Type::Atom) throw std::logic_error("Not an atom SExpression");
    return atomPtr;
}

ConsCell* SExpression::getCons() const {
    if (type != Type::ConsCell) throw std::logic_error("Not a cons cell SExpression");
    return consPtr;
}

void SExpression::print() const {
    // Print atom
    if (type == Type::Atom && atomPtr) {
        atomPtr->print();

    // Print cons cell
    } else if (type == Type::ConsCell && consPtr) {
        // Get list of s expressions in cons cell
        std::vector<SExpression*> elements = consPtr->toVector();
        if(elements.empty()) {
            Logger::log("ConsCell is empty", Logger::ERROR);
            return;
        }
        // Check if dot notation is needed (last item not nil)
        bool needsDotNotation = false;

        SExpression* last = elements.back();
        if (last->getType() == Type::Atom) {
            Atom* lastAtom = last->getAtom();
            if (lastAtom->getType() != Atom::Type::Nil) {
                needsDotNotation = true;
            }
        } else {
            needsDotNotation = true; // Last is a cons cell
        }


        std::cout << "( ";
        for (int i = 0; i < elements.size() - 1; i++) {
            // Print each element
            elements[i]->print();
            std::cout << " ";
        }
        // Print last element if dot notation
        if (needsDotNotation) {
            std::cout << ". ";
            elements.back()->print();
            std::cout << " ";
        }
        std::cout << ")";
    } else {
        Logger::log("SExpression is neither Atom nor ConsCell", Logger::ERROR);
    }
}
