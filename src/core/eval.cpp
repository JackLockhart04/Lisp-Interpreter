#include "eval.h"

SExpression* eval(SExpression* expr, Environment* env) {
    if(expr->getType() == SExpression::Type::Atom) {
        // Handle atom evaluation
        return evalAtom(expr, env);
    } else if(expr->getType() == SExpression::Type::ConsCell) {
        // Handle cons cell evaluation
        return evalList(expr, env); // FIXME implement
    }
    
    Logger::log("eval encountered unknown SExpression type", Logger::ERROR);
    return new SExpression(*expr); // Somehow not an atom or cons cell?
}

SExpression* evalAtom(SExpression* expr, Environment* env) {
    if(expr->getType() != SExpression::Type::Atom) {
        Logger::log("evalAtom called with non-atom SExpression");
        return new SExpression(*expr); // or handle error appropriately
    }

    Atom *atom = expr->getAtom();
    if(atom->getType() == Atom::Type::Nil) return new SExpression(*expr); // Nil evaluates to itself

    // Lookup symbols in environment
    if(atom->getType() == Atom::Type::Symbol) {
        SExpression *result = env->lookup(expr);
        return result;
    }

    return new SExpression(*expr);
}

SExpression* evalList(SExpression* expr, Environment* env) {
    if(expr->getType() != SExpression::Type::ConsCell) {
        // Logger::log("evalList called with non-cons cell SExpression");
        return new SExpression(*expr); // or handle error appropriately
    }

    // Evaluate the operator (car)
    SExpression *car = expr->getCons()->getCar();
    SExpression *evaluatedCar = eval(car, env);

    // Check for lambda (car will be a lambda expression)
    if(evaluatedCar->getType() == SExpression::Type::ConsCell) {
        // Check for lambda keyword at car of evaluatedCar
        SExpression *lambdaCar = evaluatedCar->getCons()->getCar();
        if(lambdaCar->getType() == SExpression::Type::Atom
                && lambdaCar->getAtom()->getType() == Atom::Type::Symbol
                && lambdaCar->getAtom()->getSymbol() == "lambda") {
            // Evaluate replace op with lambda function
            SExpression *lambdaArgs = expr->getCons()->getCdr();
            SExpression *lambdaExpr = evaluatedCar;
            SExpression *newExpr = new SExpression(new ConsCell(lambdaExpr, lambdaArgs));
            return evalLambda(newExpr, env);
        }
        // Logger::log("evalList encountered a cons cell that is not a lambda", Logger::WARNING);
    }

    // Check for predefined functions such as QUOTE
    if (evaluatedCar->getType() == SExpression::Type::Atom
            && evaluatedCar->getAtom()->getType() == Atom::Type::Symbol) {
        // Handle predefined functions
        return evalPredefinedFunction(expr, env);
    }

    // Recursively evaluate rest of list (cdr)
    SExpression *cdr = expr->getCons()->getCdr();
    SExpression *evaluatedCdr = eval(cdr, env);
    return new SExpression(new ConsCell(evaluatedCar, evaluatedCdr));
}

SExpression* evalPredefinedFunction(SExpression* expr, Environment* env) {
    // Atoms return themselves (Shouldnt even be here)
    if(expr->getType() != SExpression::Type::ConsCell) {
        return new SExpression(*expr);
    }   

    // Get the operator (car)
    SExpression *car = expr->getCons()->getCar();
    // Operators must be symbols for now FIXME to allow lambda etc
    if(car->getType() != SExpression::Type::Atom || car->getAtom()->getType() != Atom::Type::Symbol) {
        return new SExpression(*expr);
    }

    // Handle predefined functions
    std::string opSymbol = car->getAtom()->getSymbol();
    
    // -----Eval and Quote-----
    if(opSymbol == "eval") {
        // Ensure correct number of args
        int length = 0;
        if(expr->getCons()->getCdr()->getType() == SExpression::Type::ConsCell) {
            length = expr->getCons()->getCdr()->getCons()->getLength();
        }
        if(length != 1) {
            Atom *errorAtom = new Atom("Incorrect number of arguments", Atom::Type::Symbol);
            return new SExpression(errorAtom);
        }
        SExpression *cdr = expr->getCons()->getCdr();
        SExpression *arg = cdr->getCons()->getCar();
        SExpression *evalArg = eval(arg, env);
        return eval(evalArg, env);
    } else if(opSymbol == "QUOTE") {
        // Car is QUOTE, return the cdr unevaluated
        SExpression *cdr = expr->getCons()->getCdr();
        // If cons cell return its car
        if(cdr->getType() == SExpression::Type::ConsCell) {
            // Return the first element of the cdr list
            return new SExpression(*(cdr->getCons()->getCar()));
        } else { // Just an atom return itself (Only from dotted pairs)
            return new SExpression(*cdr);
        }
    }
    // List operators
    else if(opSymbol == "cons"){
        // Ensure correct number of args
        int length = 0;
        if(expr->getCons()->getCdr()->getType() == SExpression::Type::ConsCell) {
            length = expr->getCons()->getCdr()->getCons()->getLength();
        }
        if(length != 2) {
            Atom *errorAtom = new Atom("Incorrect number of arguments", Atom::Type::Symbol);
            return new SExpression(errorAtom);
        }
        SExpression *cdr = expr->getCons()->getCdr();
        SExpression *arg1 = cdr->getCons()->getCar();
        SExpression *evalArg1 = eval(arg1, env);
        SExpression *arg2 = cdr->getCons()->getCadr();
        SExpression *evalArg2 = eval(arg2, env);
        // If arg2 is an atom, add a nil to the end to make it a list unless its nil
        if(evalArg2->getType() == SExpression::Type::Atom && evalArg2->getAtom()->getType() != Atom::Type::Nil) {
            ConsCell *newCdrCons = new ConsCell(evalArg2, new SExpression());
            evalArg2 = new SExpression(newCdrCons);
        }
        return new SExpression(new ConsCell(evalArg1, evalArg2));
    } else if(opSymbol == "car") {
        // Ensure correct number of args
        int length = 0;
        if(expr->getCons()->getCdr()->getType() == SExpression::Type::ConsCell) {
            length = expr->getCons()->getCdr()->getCons()->getLength();
        }
        if(length != 1) {
            Atom *errorAtom = new Atom("Incorrect number of arguments", Atom::Type::Symbol);
            return new SExpression(errorAtom);
        }
        SExpression *cdr = expr->getCons()->getCdr();
        SExpression *arg = cdr->getCons()->getCar();
        SExpression *evalArg = eval(arg, env);
        if(evalArg->getType() != SExpression::Type::ConsCell) {
            Atom *errorAtom = new Atom("car argument is not a list", Atom::Type::Symbol);
            return new SExpression(errorAtom);
        }
        return new SExpression(*(evalArg->getCons()->getCar()));
    } else if (opSymbol == "cdr"){
        // Ensure correct number of args
        int length = 0;
        if(expr->getCons()->getCdr()->getType() == SExpression::Type::ConsCell) {
            length = expr->getCons()->getCdr()->getCons()->getLength();
        }
        if(length != 1) {
            Atom *errorAtom = new Atom("Incorrect number of arguments", Atom::Type::Symbol);
            return new SExpression(errorAtom);
        }
        SExpression *cdr = expr->getCons()->getCdr();
        SExpression *arg = cdr->getCons()->getCar();
        SExpression *evalArg = eval(arg, env);
        if(evalArg->getType() != SExpression::Type::ConsCell) {
            Atom *errorAtom = new Atom("cdr argument is not a list", Atom::Type::Symbol);
            return new SExpression(errorAtom);
        }
        return new SExpression(*(evalArg->getCons()->getCdr()));
    }
    // -----Set and Define-----
    else if (opSymbol == "set"){
        // Ensure correct number of args
        int length = 0;
        if(expr->getCons()->getCdr()->getType() == SExpression::Type::ConsCell) {
            length = expr->getCons()->getCdr()->getCons()->getLength();
        }
        if(length != 2) {
            Atom *errorAtom = new Atom("Incorrect number of arguments", Atom::Type::Symbol);
            return new SExpression(errorAtom);
        }
        SExpression *cdr = expr->getCons()->getCdr();
        SExpression *setSymbol = cdr->getCons()->getCar();
        SExpression *setValue = cdr->getCons()->getCadr();
        // Evaluate the value to be set
        SExpression *evaluatedValue = eval(setValue, env);
        env->set(setSymbol, evaluatedValue);
        return evaluatedValue;
    } else if (opSymbol == "define"){
        // Ensure correct number of args
        int length = 0;
        if(expr->getCons()->getCdr()->getType() == SExpression::Type::ConsCell) {
            length = expr->getCons()->getCdr()->getCons()->getLength();
        }
        if(length != 3) {
            Atom *errorAtom = new Atom("Incorrect number of arguments", Atom::Type::Symbol);
            return new SExpression(errorAtom);
        }
        // Define is set a lambda function to a symbol
        SExpression *cdr = expr->getCons()->getCdr();

        SExpression *defineSymbol = cdr->getCons()->getCar();
        SExpression *defineValue = cdr->getCons()->getCdr();
        // Add lambda keyword to beginning of defineValue list
        SExpression *lambdaSymbol = new SExpression(new Atom("lambda", Atom::Type::Symbol));
        SExpression *lambdaList = new SExpression(new ConsCell(lambdaSymbol, defineValue));
        // QUOTE the lambda list
        // SExpression *quoteExpr = new SExpression(new Atom("QUOTE", Atom::Type::Symbol));
        // lambdaList = new SExpression(new ConsCell(quoteExpr, lambdaList));
        // Set the symbol to the quoted lambda list
        env->set(defineSymbol, lambdaList);

        return lambdaList;
    }
    // -----Conditionals-----
    else if (opSymbol == "and") {
        // Ensure correct number of args
        int length = 0;
        if(expr->getCons()->getCdr()->getType() == SExpression::Type::ConsCell) {
            length = expr->getCons()->getCdr()->getCons()->getLength();
        }
        if(length != 2) {
            Atom *errorAtom = new Atom("Incorrect number of arguments", Atom::Type::Symbol);
            return new SExpression(errorAtom);
        }
        SExpression *cdr = expr->getCons()->getCdr();
        SExpression *arg1 = cdr->getCons()->getCar();
        SExpression *arg2 = cdr->getCons()->getCadr();
        
        return Conditional::and_(arg1, arg2, env);
    } else if (opSymbol == "or"){
        // Ensure correct number of args
        int length = 0;
        if(expr->getCons()->getCdr()->getType() == SExpression::Type::ConsCell) {
            length = expr->getCons()->getCdr()->getCons()->getLength();
        }
        if(length != 2) {
            Atom *errorAtom = new Atom("Incorrect number of arguments", Atom::Type::Symbol);
            return new SExpression(errorAtom);
        }
        SExpression *cdr = expr->getCons()->getCdr();
        SExpression *arg1 = cdr->getCons()->getCar();
        SExpression *arg2 = cdr->getCons()->getCadr();
        
        return Conditional::or_(arg1, arg2, env);
    } else if (opSymbol == "if"){
        // Ensure correct number of args
        int length = 0;
        if(expr->getCons()->getCdr()->getType() == SExpression::Type::ConsCell) {
            length = expr->getCons()->getCdr()->getCons()->getLength();
        }
        if(length != 3) {
            Atom *errorAtom = new Atom("Incorrect number of arguments", Atom::Type::Symbol);
            return new SExpression(errorAtom);
        }
        SExpression *cdr = expr->getCons()->getCdr();
        SExpression *arg1 = cdr->getCons()->getCar();
        SExpression *arg2 = cdr->getCons()->getCadr();
        SExpression *arg3 = cdr->getCons()->getCaddr();

        return Conditional::if_(arg1, arg2, arg3, env);
    } else if (opSymbol == "cond"){
        // Ensure correct number of args
        int length = 0;
        if(expr->getCons()->getCdr()->getType() == SExpression::Type::ConsCell) {
            length = expr->getCons()->getCdr()->getCons()->getLength();
        }
        if(length < 1) {
            Atom *errorAtom = new Atom("Incorrect number of arguments", Atom::Type::Symbol);
            return new SExpression(errorAtom);
        }
        SExpression *cdr = expr->getCons()->getCdr();
        return Conditional::cond(cdr, env);
    }
    // -----Arithmetic-----
    else if (opSymbol == "+"){
        // Ensure correct number of args
        int length = 0;
        if(expr->getCons()->getCdr()->getType() == SExpression::Type::ConsCell) {
            length = expr->getCons()->getCdr()->getCons()->getLength();
        }
        if(length != 2) {
            Atom *errorAtom = new Atom("Incorrect number of arguments", Atom::Type::Symbol);
            return new SExpression(errorAtom);
        }
        SExpression *num1 = expr->getCons()->getCadr();
        SExpression *evalNum1 = eval(num1, env);
        SExpression *num2 = expr->getCons()->getCaddr();
        SExpression *evalNum2 = eval(num2, env);
        return NumberFunction::add(evalNum1, evalNum2);
    } else if (opSymbol == "-"){
        // Ensure correct number of args
        int length = 0;
        if(expr->getCons()->getCdr()->getType() == SExpression::Type::ConsCell) {
            length = expr->getCons()->getCdr()->getCons()->getLength();
        }
        if(length != 2) {
            Atom *errorAtom = new Atom("Incorrect number of arguments", Atom::Type::Symbol);
            return new SExpression(errorAtom);
        }
        SExpression *num1 = expr->getCons()->getCadr();
        SExpression *evalNum1 = eval(num1, env);
        SExpression *num2 = expr->getCons()->getCaddr();
        SExpression *evalNum2 = eval(num2, env);
        return NumberFunction::sub(evalNum1, evalNum2);
    } else if (opSymbol == "*"){
        // Ensure correct number of args
        int length = 0;
        if(expr->getCons()->getCdr()->getType() == SExpression::Type::ConsCell) {
            length = expr->getCons()->getCdr()->getCons()->getLength();
        }
        if(length != 2) {
            Atom *errorAtom = new Atom("Incorrect number of arguments", Atom::Type::Symbol);
            return new SExpression(errorAtom);
        }
        SExpression *num1 = expr->getCons()->getCadr();
        SExpression *evalNum1 = eval(num1, env);
        SExpression *num2 = expr->getCons()->getCaddr();
        SExpression *evalNum2 = eval(num2, env);
        return NumberFunction::mul(evalNum1, evalNum2);
    } else if (opSymbol == "/"){
        // Ensure correct number of args
        int length = 0;
        if(expr->getCons()->getCdr()->getType() == SExpression::Type::ConsCell) {
            length = expr->getCons()->getCdr()->getCons()->getLength();
        }
        if(length != 2) {
            Atom *errorAtom = new Atom("Incorrect number of arguments", Atom::Type::Symbol);
            return new SExpression(errorAtom);
        }
        SExpression *num1 = expr->getCons()->getCadr();
        SExpression *evalNum1 = eval(num1, env);
        SExpression *num2 = expr->getCons()->getCaddr();
        SExpression *evalNum2 = eval(num2, env);
        return NumberFunction::div(evalNum1, evalNum2);
    } else if (opSymbol == "mod"){
        // Ensure correct number of args
        int length = 0;
        if(expr->getCons()->getCdr()->getType() == SExpression::Type::ConsCell) {
            length = expr->getCons()->getCdr()->getCons()->getLength();
        }
        if(length != 2) {
            Atom *errorAtom = new Atom("Incorrect number of arguments", Atom::Type::Symbol);
            return new SExpression(errorAtom);
        }
        SExpression *num1 = expr->getCons()->getCadr();
        SExpression *evalNum1 = eval(num1, env);
        SExpression *num2 = expr->getCons()->getCaddr();
        SExpression *evalNum2 = eval(num2, env);
        return NumberFunction::mod(evalNum1, evalNum2);
    }
    // -----Comparison-----
    else if (opSymbol == "<"){
        // Ensure correct number of args
        int length = 0;
        if(expr->getCons()->getCdr()->getType() == SExpression::Type::ConsCell) {
            length = expr->getCons()->getCdr()->getCons()->getLength();
        }
        if(length != 2) {
            Atom *errorAtom = new Atom("Incorrect number of arguments", Atom::Type::Symbol);
            return new SExpression(errorAtom);
        }
        SExpression *num1 = expr->getCons()->getCadr();
        SExpression *evalNum1 = eval(num1, env);
        SExpression *num2 = expr->getCons()->getCaddr();
        SExpression *evalNum2 = eval(num2, env);
        return NumberFunction::lt(evalNum1, evalNum2);
    } else if (opSymbol == ">"){
        // Ensure correct number of args
        int length = 0;
        if(expr->getCons()->getCdr()->getType() == SExpression::Type::ConsCell) {
            length = expr->getCons()->getCdr()->getCons()->getLength();
        }
        if(length != 2) {
            Atom *errorAtom = new Atom("Incorrect number of arguments", Atom::Type::Symbol);
            return new SExpression(errorAtom);
        }
        SExpression *num1 = expr->getCons()->getCadr();
        SExpression *evalNum1 = eval(num1, env);
        SExpression *num2 = expr->getCons()->getCaddr();
        SExpression *evalNum2 = eval(num2, env);
        return NumberFunction::gt(evalNum1, evalNum2);
    } else if (opSymbol == "<="){
        // Ensure correct number of args
        int length = 0;
        if(expr->getCons()->getCdr()->getType() == SExpression::Type::ConsCell) {
            length = expr->getCons()->getCdr()->getCons()->getLength();
        }
        if(length != 2) {
            Atom *errorAtom = new Atom("Incorrect number of arguments", Atom::Type::Symbol);
            return new SExpression(errorAtom);
        }
        SExpression *num1 = expr->getCons()->getCadr();
        SExpression *evalNum1 = eval(num1, env);
        SExpression *num2 = expr->getCons()->getCaddr();
        SExpression *evalNum2 = eval(num2, env);
        return NumberFunction::lte(evalNum1, evalNum2);
    } else if (opSymbol == ">="){
        // Ensure correct number of args
        int length = 0;
        if(expr->getCons()->getCdr()->getType() == SExpression::Type::ConsCell) {
            length = expr->getCons()->getCdr()->getCons()->getLength();
        }
        if(length != 2) {
            Atom *errorAtom = new Atom("Incorrect number of arguments", Atom::Type::Symbol);
            return new SExpression(errorAtom);
        }
        SExpression *num1 = expr->getCons()->getCadr();
        SExpression *evalNum1 = eval(num1, env);
        SExpression *num2 = expr->getCons()->getCaddr();
        SExpression *evalNum2 = eval(num2, env);
        return NumberFunction::gte(evalNum1, evalNum2);
    } else if (opSymbol == "="){
        // Ensure correct number of args
        int length = 0;
        if(expr->getCons()->getCdr()->getType() == SExpression::Type::ConsCell) {
            length = expr->getCons()->getCdr()->getCons()->getLength();
        }
        if(length != 2) {
            Atom *errorAtom = new Atom("Incorrect number of arguments", Atom::Type::Symbol);
            return new SExpression(errorAtom);
        }
        SExpression *num1 = expr->getCons()->getCadr();
        SExpression *evalNum1 = eval(num1, env);
        SExpression *num2 = expr->getCons()->getCaddr();
        SExpression *evalNum2 = eval(num2, env);
        return LogicalFunction::eq(evalNum1, evalNum2);
    } else if (opSymbol == "not"){
        // Ensure correct number of args
        int length = 0;
        if(expr->getCons()->getCdr()->getType() == SExpression::Type::ConsCell) {
            length = expr->getCons()->getCdr()->getCons()->getLength();
        }
        if(length != 1) {
            Atom *errorAtom = new Atom("Incorrect number of arguments", Atom::Type::Symbol);
            return new SExpression(errorAtom);
        }
        SExpression *arg = expr->getCons()->getCadr();
        SExpression *evalArg = eval(arg, env);
        return LogicalFunction::logical_not(evalArg);
    }
    // Types
    else if (opSymbol == "atom?"){
        // Ensure correct number of args
        int length = 0;
        if(expr->getCons()->getCdr()->getType() == SExpression::Type::ConsCell) {
            length = expr->getCons()->getCdr()->getCons()->getLength();
        }
        if(length != 1) {
            Atom *errorAtom = new Atom("Incorrect number of arguments", Atom::Type::Symbol);
            return new SExpression(errorAtom);
        }
        SExpression *arg = expr->getCons()->getCadr();
        SExpression *evalArg = eval(arg, env);
        Atom *resultAtom;
        if(evalArg->getType() == SExpression::Type::Atom && evalArg->getAtom()->getType() != Atom::Type::Nil) {
            resultAtom = new Atom("t", Atom::Type::Symbol); // true
        } else {
            resultAtom = new Atom(); // nil (false)
        }
        return new SExpression(resultAtom);
    } else if (opSymbol == "list?"){
        // Ensure correct number of args
        int length = 0;
        if(expr->getCons()->getCdr()->getType() == SExpression::Type::ConsCell) {
            length = expr->getCons()->getCdr()->getCons()->getLength();
        }
        if(length != 1) {
            Atom *errorAtom = new Atom("Incorrect number of arguments", Atom::Type::Symbol);
            return new SExpression(errorAtom);
        }
        SExpression *arg = expr->getCons()->getCadr();
        SExpression *evalArg = eval(arg, env);
        Atom *resultAtom;
        if(evalArg->getType() == SExpression::Type::ConsCell || (evalArg->getType() == SExpression::Type::Atom && evalArg->getAtom()->getType() == Atom::Type::Nil)) {
            resultAtom = new Atom("t", Atom::Type::Symbol); // true
        } else {
            resultAtom = new Atom(); // nil (false)
        }
        return new SExpression(resultAtom);
    } else if (opSymbol == "nil?"){
        // Ensure correct number of args
        int length = 0;
        if(expr->getCons()->getCdr()->getType() == SExpression::Type::ConsCell) {
            length = expr->getCons()->getCdr()->getCons()->getLength();
        }
        if(length != 1) {
            Atom *errorAtom = new Atom("Incorrect number of arguments", Atom::Type::Symbol);
            return new SExpression(errorAtom);
        }
        SExpression *arg = expr->getCons()->getCadr();
        SExpression *evalArg = eval(arg, env);
        Atom *resultAtom;
        if(evalArg->getType() == SExpression::Type::Atom && evalArg->getAtom()->getType() == Atom::Type::Nil) {
            resultAtom = new Atom("t", Atom::Type::Symbol); // true
        } else {
            resultAtom = new Atom(); // nil (false)
        }
        return new SExpression(resultAtom);
    } else if (opSymbol == "number?"){
        // Ensure correct number of args
        int length = 0;
        if(expr->getCons()->getCdr()->getType() == SExpression::Type::ConsCell) {
            length = expr->getCons()->getCdr()->getCons()->getLength();
        }
        if(length != 1) {
            Atom *errorAtom = new Atom("Incorrect number of arguments", Atom::Type::Symbol);
            return new SExpression(errorAtom);
        }
        SExpression *arg = expr->getCons()->getCadr();
        SExpression *evalArg = eval(arg, env);
        Atom *resultAtom;
        if(TypeChecker::isNumber(evalArg)) {
            resultAtom = new Atom("t", Atom::Type::Symbol); // true
        } else {
            resultAtom = new Atom(); // nil (false)
        }
        return new SExpression(resultAtom);
    }

    return new SExpression(*expr); // Return a copy of the expression if cant do anything
}

SExpression* evalLambda(SExpression* expr, Environment* env) {
    // Logger::log("Evaluating lambda function", Logger::INFO);
    // Handle lambda function
    // Get parameters and body
    SExpression *lambdaExpr = expr->getCons()->getCar();
    SExpression *params = lambdaExpr->getCons()->getCadr();
    int paramLength = 0;
    if(params->getType() == SExpression::Type::ConsCell) {
        paramLength = params->getCons()->getLength();
    }
    SExpression *body = lambdaExpr->getCons()->getCaddr();

    // Get arguments from original expr (cdr)
    SExpression *args = expr->getCons()->getCdr();
    int argLength = 0;
    if(args->getType() == SExpression::Type::ConsCell) {
        argLength = args->getCons()->getLength();
    }
    // Check for correct number of arguments
    if(paramLength != argLength) {
        // Logger::log("Lambda function called with incorrect number of arguments", Logger::ERROR);
        Atom *errorAtom = new Atom("Incorrect number of arguments", Atom::Type::Symbol);
        return new SExpression(errorAtom);
    }
    // Evaluate arguments
    args = evalList(args, env);

    // Create new environment for lambda application
    Environment *lambdaEnv = new Environment(env, params, args);
    // Logger::log("Lambda environment created", Logger::INFO);
    // Evaluate body in new environment
    return eval(body, lambdaEnv);
}