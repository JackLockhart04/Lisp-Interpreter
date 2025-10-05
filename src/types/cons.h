#pragma once

#include "types/s_expression.h"

#include <memory>
#include <vector>

class ConsCell {
public:
    ConsCell(SExpression* car, SExpression* cdr);
    ConsCell(const ConsCell& other);
    ~ConsCell();

    SExpression* getCar();
    SExpression* getCdr();
    SExpression* getCadr();
    SExpression* getCaddr();

    int getLength();
    void print() const;
    std::vector<SExpression*> toVector();

private:
    SExpression* car;
    SExpression* cdr;
};