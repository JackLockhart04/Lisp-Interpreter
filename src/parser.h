#pragma once

#include "scanner.h"
#include "types/s_expression.h"
#include "types/atom.h"
#include "types/cons.h"
#include "types/token.h"

#include <memory>
#include <iostream>
#include <string>

class Parser {
public:
	Parser(const std::string& filename = "");
	SExpression* parseSExpression();

private:
	SExpression* parseList(); // New method for parsing lists
	Scanner* scanner;
};
