#include "s_expression.h"
#include "atom.h"
#include "cons.h"

#include <iostream>
#include <memory>
#include <stdexcept>

SExpression::SExpression() {
    type = Type::Atom;
    atomPtr = new Atom(); // Default to nil atom
    consPtr = nullptr;
}

SExpression::SExpression(const SExpression& other) {
    type = other.getType();
    if (type == Type::Atom) {
        atomPtr = new Atom(*(other.getAtom()));
        consPtr = nullptr;
    } else if (type == Type::ConsCell) {
        consPtr = new ConsCell(*(other.getCons()));
        atomPtr = nullptr;
    } else {
        throw std::logic_error("Unknown SExpression type in copy constructor");
    }
}

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
    if (type != Type::Atom){
        Logger::log("getAtom called on non-atom SExpression", Logger::ERROR);
        Atom *nil = new Atom(); // Nil atom
        return nil;
    }
    return atomPtr;
}

ConsCell* SExpression::getCons() const {
    if (type != Type::ConsCell){
        Logger::log("getCons called on non-cons cell SExpression", Logger::ERROR);
        ConsCell *nil = new ConsCell(new SExpression(), new SExpression());
        return nil;
    }
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
