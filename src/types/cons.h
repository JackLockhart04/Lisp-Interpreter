#pragma once

#include "types/s_expression.h"

#include <memory>
#include <vector>

class ConsCell {
public:
    ConsCell(SExpression* car, SExpression* cdr);
    ~ConsCell();

    SExpression& getCar();
    SExpression& getCdr();

    void print() const;
    std::vector<SExpression*> toVector();

private:
    SExpression* car;
    SExpression* cdr;
};