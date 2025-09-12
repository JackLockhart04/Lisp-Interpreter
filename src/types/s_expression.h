#pragma once

#include <vector>

class Atom;
class ConsCell;

class SExpression {
public:
    enum class Type {
        Atom,
        ConsCell
    };

    // Constructors for atom and cons cell
    SExpression(Atom* atom);
    SExpression(ConsCell* cons);
    ~SExpression();

    Type getType() const;
    Atom* getAtom() const;
    ConsCell* getCons() const;

    void print() const;

private:
    Type type;
    Atom* atomPtr;
    ConsCell* consPtr;
};


