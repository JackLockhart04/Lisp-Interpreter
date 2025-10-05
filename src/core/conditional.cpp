#include "conditional.h"

SExpression* Conditional::and_(SExpression* expr1, SExpression* expr2, Environment* env) {
    SExpression *result1 = eval(expr1, env);
    if(!LogicalFunction::isTrue(result1)) {
        return new SExpression(); // Return nil if first expression is false
    }

    return eval(expr2, env); // Return the evaluation of the second expression
}

SExpression* Conditional::or_(SExpression* expr1, SExpression* expr2, Environment* env) {
    SExpression *result1 = eval(expr1, env);
    if(LogicalFunction::isTrue(result1)) {
        return new SExpression(new Atom("t", Atom::Type::Symbol)); // Return true
    }

    return eval(expr2, env); // Return the evaluation of the second expression
}

SExpression* Conditional::if_(SExpression* expr1, SExpression* expr2, SExpression* expr3, Environment* env) {
    SExpression *condition = eval(expr1, env);
    if(LogicalFunction::isTrue(condition)) {
        return eval(expr2, env); // Evaluate and return the 'then' branch
    } else {
        return eval(expr3, env); // Evaluate and return the 'else' branch
    }
}

SExpression* Conditional::cond(SExpression* expr, Environment* env) {
    SExpression *clauses = expr;
    while(clauses->getType() == SExpression::Type::ConsCell) {
        SExpression *clause = clauses->getCons()->getCar();
        SExpression *condition = clause->getCons()->getCar();
        SExpression *body = clause->getCons()->getCadr();

        if(LogicalFunction::isTrue(eval(condition, env))) {
            return eval(body, env);
        }

        clauses = clauses->getCons()->getCdr();
    }

    return new SExpression(); // Return nil if no clauses matched
}
