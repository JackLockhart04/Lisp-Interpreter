1. README

    # Use

        Builds end up in `build` dir.
        Run `main` for use with stdin.
        Run `main < 'filename'` for file as stdin.
        Run `main 'filename'` to read from file. Has better output formatting.

        ### In code

            Logger levels: DEBUG, INFO, WARNING, ERROR, CRITICAL.
                Most used are INFO and ERROR.
                Prints any messages of lowest level set and any of higher priority.

    # Structure

        src dir has the source code and main.cpp
        tests dir has the test code and test main.cpp
        Files organized into sections such as types, core, and util

    # Building

        ### Makefile

                From root dir, run `make`
                Creates 'main.exe' and 'tests_main.exe' in the build dir

        ### CMake

            First time, from build dir, need to run `cmake ..`
            From build dir, run `cmake --build .`
            Creates 'main.exe' and 'tests.exe' in the build dir

            ##### Tests

                From build dir, run `cmake --build .`
                Creates 'tests.exe' in the build dir

2. Test plan

    Separated into classes based on what is being tested.
    Ex: Testing atoms in types/atom_test.cpp
    Use classes to organize static methods to call from test main.
    Main keeps track of how many total succeed and fail.
    Successful tests print out with Logger level INFO or lower.
    Failed tests print out with Logger level ERROR or lower.

    Currently testing input handling, atoms, cons cells, and s expressions.

    # Tests

        ### Input handling

            Reader to ensure reading from file works.
            Scanner to ensure tokenization works.

        ### Types

            Atoms tested by creating and using created atoms
            Cons Cells tested by creating and using cons cells. FIXME add nested list testing but works by hand.
            S Expression tested by creating s expressions with atoms and cons cells.

        ### Core

            Ensure all core functinoalities are working
            Each core class has its own tests included in ./tests except for eval() which is tested mostly with my 'testFile.lisp'

3. Test output

    # Automatic testing

        $ ./tests
        INFO: ----- Input handling Tests -----
        > 0123456789
        > abcdefghijklmnopqrstuvwxyz
        > ABCDEFGHIJKLMNOPQRSTUVWXYZ
        > !"#$%&'()*+,-./:;<=>?@[\]^_`{|}~
        >  
        > 
        > 
        > "'`\
        INFO: PASS: Reader tests passed.
        > 42
        > 1.2
        > 1.2.3
        > Hello world; this shouldn't print
        > "Roll tide"
        > (Roll tide)
        > ( (1)
        >  (2)
        > (3) )
        INFO: PASS: Scanner tests passed.
        INFO: ----- Atom tests -----
        INFO: PASS: getString
        INFO: PASS: getSymbol
        INFO: PASS: getLong
        INFO: PASS: getDouble
        INFO: PASS: getType
        INFO: ----- Cons tests -----
        INFO: PASS: car
        INFO: PASS: cdr
        INFO: PASS: toVector size
        INFO: PASS: toVector contents
        INFO: ----- SExpression tests -----
        INFO: PASS: atom SExpression getType
        INFO: PASS: cons SExpression getType
        INFO: PASS: atom SExpression getAtom
        INFO: PASS: cons SExpression getCons
        INFO: ----- TypeChecker tests -----
        INFO: PASS: Nil expression is correctly identified as nil.
        INFO: PASS: Number expression is correctly identified as NOT nil.
        INFO: PASS: Long expression is correctly identified as number.
        INFO: PASS: Double expression is correctly identified as number.
        INFO: PASS: String expression is correctly identified as NOT number.
        INFO: PASS: Symbol expression is correctly identified as symbol.
        INFO: PASS: String expression is correctly identified as NOT symbol.
        INFO: PASS: String expression is correctly identified as string.
        INFO: PASS: Number expression is correctly identified as NOT string.
        INFO: PASS: Cons cell expression is correctly identified as list.
        INFO: PASS: Nil expression is correctly identified as list.
        INFO: PASS: Number expression is correctly identified as NOT list.
        INFO: ----- NumberFunction tests -----
        INFO: PASS: Long addition is correct.
        INFO: PASS: Double addition is correct.
        INFO: PASS: Mixed addition correctly not allowed.
        INFO: PASS: Addition with nil is correctly an error.
        INFO: PASS: Addition with string is correctly an error.
        INFO: PASS: Long subtraction is correct.
        INFO: PASS: Double subtraction is correct.
        INFO: PASS: Mixed subtraction is correctly not allowed.
        INFO: PASS: Subtraction with nil is correctly an error.
        INFO: PASS: Subtraction with string is correctly an error.
        INFO: PASS: Long multiplication is correct.
        INFO: PASS: Double multiplication is correct.
        INFO: PASS: Mixed multiplication is correctly not allowed.
        INFO: PASS: Multiplication with nil is correctly an error.
        INFO: PASS: Multiplication with string is correctly an error.
        INFO: PASS: Long division is correct.
        INFO: PASS: Double division is correct.
        INFO: PASS: Mixed division (long/double) is correctly not allowed.
        INFO: PASS: Mixed division (double/long) is correctly not allowed.
        INFO: PASS: Division by zero (long) is correctly an error.
        INFO: PASS: Division by zero (double) is correctly an error.
        INFO: PASS: Division with nil is correctly an error.
        INFO: PASS: Division with string is correctly an error.
        INFO: PASS: Long modulus is correct.
        INFO: PASS: Modulus by zero is correctly an error.
        INFO: PASS: Modulus with double is correctly an error.
        INFO: PASS: Modulus with nil is correctly an error.
        INFO: PASS: Long less than is correct.
        INFO: PASS: Long not less than is correct.
        INFO: PASS: Double less than is correct.
        INFO: PASS: Double not less than is correct.
        INFO: PASS: Mixed less than (long < double) is correctly an error.
        INFO: PASS: Mixed not less than (long < double) is correctly an error.
        INFO: PASS: Less than with string is correctly an error.
        INFO: PASS: Less than with nil is correctly an error.
        INFO: PASS: Long less/equal than is correct.
        INFO: PASS: Long not less/equal than is correct.
        INFO: PASS: Long less than/equal is correct.
        INFO: PASS: Double less than/equal is correct.
        INFO: PASS: Double not less than/equal is correct.
        INFO: PASS: Double less than/equal is correct.
        INFO: PASS: Mixed less than/equal (long < double) is correctly an error.
        INFO: PASS: Mixed not less/equal than (long < double) is correctly an error.
        INFO: PASS: Less than/equal with string is correctly an error.
        INFO: PASS: Less than/equal with nil is correctly an error.
        INFO: PASS: Long greater than is correct.
        INFO: PASS: Long not greater than is correct.
        INFO: PASS: Double greater than is correct.
        INFO: PASS: Double not greater than is correct.
        INFO: PASS: Mixed greater than (long > double) is correctly an error.
        INFO: PASS: Mixed not greater than (long > double) is correctly an error.
        INFO: PASS: Greater than with string is correctly an error.
        INFO: PASS: Greater than with nil is correctly an error.
        INFO: PASS: Long greater/equal than is correct.
        INFO: PASS: Long not greater/equal than is correct.
        INFO: PASS: Long greater/equal is correct.
        INFO: PASS: Double greater/equal is correct.
        INFO: PASS: Double not greater/equal is correct.
        INFO: PASS: Double greater/equal is correct.
        INFO: PASS: Mixed greater/equal (long > double) is correctly an error.
        INFO: PASS: Mixed not greater/equal (long > double) is correctly an error.
        INFO: PASS: Greater/equal with string is correctly an error.
        INFO: PASS: Greater/equal with nil is correctly an error.
        INFO: ----- LogicalFunction tests -----
        INFO: PASS: Long equality is correct.
        INFO: PASS: Long inequality is correct.
        INFO: PASS: Double equality is correct.
        INFO: PASS: Double inequality is correct.
        INFO: PASS: Symbol equality is correct.
        INFO: PASS: Symbol inequality is correct.
        INFO: PASS: String equality is correct.
        INFO: PASS: String inequality is correct.
        INFO: PASS: Nil equality is correct.
        INFO: PASS: Different type inequality is correct.
        INFO: PASS: Different type with nil inequality is correct.
        INFO: PASS: Not nil -> t is correct.
        INFO: PASS: Non-nil -> nil is correct.
        INFO: PASS: Not non-atom is correct.
        INFO: ----- Conditional tests -----
        INFO: PASS: and_ true/true returns second expr.
        INFO: PASS: and_ false/true returns false.
        INFO: PASS: and_ true/false returns false.
        INFO: PASS: or_ true/true returns first expr.
        INFO: PASS: or_ false/true returns true.
        INFO: PASS: or_ true/false returns true.
        INFO: PASS: if_ true returns then expr.
        INFO: PASS: if_ false returns else expr.
        INFO: PASS: cond returns correct value for first true case.
        INFO: PASS: cond returns correct value for second true case.
        INFO: ----- Environment tests -----
        INFO: PASS: Set and lookup 1 variable
        INFO: PASS: Set and lookup 2 variable
        INFO: PASS: Update Environment variable 'y'
        INFO: PASS: lookup non-existing variable returns itself
        INFO: PASS: lookup invalid variable returns itself
        INFO: PASS: Set and lookup ConsCell
        INFO: PASS: lookup nil returns itself
        INFO: Tests complete.
        INFO: Passes: 121
        INFO: Fails: 0

    # Manual

        $ ./main ../testFile.lisp
        > ; Basic value evaluation
        > 42
        : 42
        > hello
        : hello
        > "world"
        : "world"
        > ()
        : ()
        > 
        > ; Arithmetic
        > (+ 1 2)
        : 3
        > (* 3 4)
        : 12
        > (- 10 5)
        : 5
        > (/ 20 4)
        : 5
        > (mod 10 3)
        : 1
        >
        > ; Equalities
        > (= 1 1)
        : t
        > (= 1 2)
        : ()
        > (= "hello" "hello")
        : t
        > (= "world" world)
        : ()
        > (< 1 2)
        : t
        > (< 2 1)
        : ()
        > (>= 2 1)
        : t
        > (>= 2 2)
        : t
        > (>= 1 2)
        : ()
        >
        > ; Variable definition and usage
        > (set x '7)
        : 7
        > (set y '3)
        : 3
        > (+ x y)
        : 10
        > (set z x)
        : 7
        > z
        : 7
        > (set z 'x)
        : x
        > z
        : x
        > (set z (QUOTE y))
        : y
        >
        > ; Conditionals
        > (and 1 2)
        : 2
        > (and () 2)
        : ()
        > (and 1 ())
        : ()
        > (or 1 2)
        : t
        > (or () 2)
        : 2
        > (or 1 ())
        : t
        > (if (> 1 2) "1 is greater" "2 is greater or equal")
        : "2 is greater or equal"
        > (if () '1 '2)
        : 2
        > (if 't '1 '2)
        : 1
        > (cond ('t '1) (() '2))
        : 1
        > (cond (() '1) ('t '2))
        : 2
        > (not '1)
        : ()
        > (not ())
        : t
        >
        > ; Function definition and call
        > (define square (n) (* n n))
        : ( lambda ( n ) ( * n n ) )
        > (square 5)
        : 25
        > (define cube (n) (* n (square n))) ; nested
        : ( lambda ( n ) ( * n ( square n ) ) )
        > (cube 5)
        : 125
        > (define fact (n) (if (= n 0) 1 (* n (fact (- n 1))))) ; recursion
        : ( lambda ( n ) ( if ( = n 0 ) 1 ( * n ( fact ( - n 1 ) ) ) ) )
        > (fact 5)
        : 120
        > ((lambda (n) (+ n 1)) 5)
        : 6
        > (set increment (lambda (n) (+ n 1))) ; Set with lambda
        : ( lambda ( n ) ( + n 1 ) )
        > (increment 2)
        : 3
        >
        >
        > ; List construction
        > (cons '1 (cons '2 '3))
        : ( 1 2 3 )
        >
        > ; Errors
        > (+ 1 'a)
        : "Not numbers"
        > (< 1 'a)
        : "Not numbers"
        > (+ 1 1.1)
        : "Not same type"
        > (+ 1)
        : Incorrect number of arguments
        > (/ 1 0)
        : "Division by zero"
        > (set a)
        : Incorrect number of arguments
        > (define a)
        : Incorrect number of arguments
        > INFO: Exiting normally.

    # Bowling

        $ ./main ../bowling.lisp
        > ;bowling ten frame
        > ;strike = first throw = 10
        > ;spare = first + second = 10
        > ;strike countes 10 plus next two throws
        > ;spare counts 10 plus next throw
        > ;otherwise  frame is sum of two throws
        > ;tenth frame is special - chance for extra throws
        > ;  1    2    3    4    5    6    7    8    9    10
        > ;[10|][5|5][10|][6|3][ | ][ | ][ | ][ | ][ | ][ | , ]
        > ;  20  40   59 ....
        > ;lis => '(10   5 5  10   6 3  10    7 3 9 1   10 8 0  5 5 5)
        > 
        > (define cadr(lis) (car (cdr lis)))
        : ( lambda ( lis ) ( car ( cdr lis ) ) )
        > (define cddr(lis) (cdr (cdr lis)))
        : ( lambda ( lis ) ( cdr ( cdr lis ) ) )
        > (define caddr(lis) (car (cddr lis)))
        : ( lambda ( lis ) ( car ( cddr lis ) ) )
        > (define cdddr(lis) (cdr (cddr lis)))
        : ( lambda ( lis ) ( cdr ( cddr lis ) ) )
        >
        > (define strike? (lis) (= 10 (car lis)) )
        : ( lambda ( lis ) ( = 10 ( car lis ) ) )
        > (define spare? (lis) (= 10 (sum2 lis)) )
        : ( lambda ( lis ) ( = 10 ( sum2 lis ) ) )
        > (define sum2(lis)
        >       (+ (car lis) (cadr lis))
        > )
        : ( lambda ( lis ) ( + ( car lis ) ( cadr lis ) ) )
        > (define sum3(lis)
        >       (+ (sum2 lis)(caddr lis))
        > )
        : ( lambda ( lis ) ( + ( sum2 lis ) ( caddr lis ) ) )
        > (define drop1 (lis) (cdr lis) )
        : ( lambda ( lis ) ( cdr lis ) )
        > (define drop2 (lis) (cddr lis) )
        : ( lambda ( lis ) ( cddr lis ) )
        > (define drop (lis) (cond
        >     ((spare? lis) (drop2 lis))
        >       ((strike? lis) (drop1 lis))
        >       ('t (drop2 lis))
        > ))
        : ( lambda ( lis ) ( cond ( ( spare? lis ) ( drop2 lis ) ) ( ( strike? lis ) ( drop1 lis ) ) ( ( QUOTE t ) ( drop2 lis ) ) ) )  
        >
        > (define bowlingscore (lis)
        >       (bowling lis 1)
        > )
        : ( lambda ( lis ) ( bowling lis 1 ) )
        > (define add1 (x) (+ 1 x))
        : ( lambda ( x ) ( + 1 x ) )
        > (define bowling(lis frame#)(cond
        >       ((= frame# 11) 0)
        >       ('t (+ (scorethisframe lis)
        >               (bowling (drop lis) (add1 frame#))))
        > ))
        : ( lambda ( lis frame# ) ( cond ( ( = frame# 11 ) 0 ) ( ( QUOTE t ) ( + ( scorethisframe lis ) ( bowling ( drop lis ) ( add1 frame# ) ) ) ) ) )
        > (define scorethisframe (lis)(cond
        >       ((or (strike? lis) (spare? lis)) (sum3 lis))
        >       ('t (sum2 lis))
        > ))
        : ( lambda ( lis ) ( cond ( ( or ( strike? lis ) ( spare? lis ) ) ( sum3 lis ) ) ( ( QUOTE t ) ( sum2 lis ) ) ) )
        >
        > (bowlingscore '(
        >     0 0
        >     0 0
        >     0 0
        >     0 0
        >     0 0
        >     0 0
        >     0 0
        >     0 0
        >     0 0
        >     0 0
        >      )
        > )
        : 0
        > (bowlingscore '(
        >     0 1
        >     0 1
        >     0 1
        >     0 1
        >     0 1
        >     0 1
        >     0 1
        >     0 1
        >     0 1
        >     0 1
        >      )
        > )
        : 10
        > (bowlingscore '(
        >     0 1;1
        >     2 3;6
        >     4 5;15
        >     6 3;24
        >     7 2;33
        >     8 1;42
        >     9 0;51
        >     1 8;60
        >     3 6;69
        >     5 4;78
        >      )
        > )
        : 78
        > (bowlingscore '(
        >     0 10
        >     0 10
        >     0 10
        >     0 10
        >     0 10
        >     0 10
        >     0 10
        >     0 10
        >     0 10
        >     0 10 0
        >      )
        > )
        : 100
        > (bowlingscore '(
        >     10
        >     10
        >     10
        >     10
        >     10
        >     10
        >     10
        >     10
        >     10
        >     10 10 10
        >      )
        > )
        : 300
        >
        >
        >
        >
        >
        >
        >
        >
        >
        >
        >
        >
        >
        >
        >
        > INFO: Exiting normally.

4. Documentation

    ### Limitations

        Cannot read in dot notation
        Cannot start symbols with reserved characters like '+'
        Doesn't have extra built in functionalities like cadr, maps, etc

    ### Design Choices

        ##### Symbols

            Start: Currently cannot start with numbers, 1 char keywords, numbers, or a few other special cases like \
            Characters: Currently cannot include single letter keywords like '(' or things like that. But that also includes '.', '+', etc

        ##### Numbers

            Numbers with multiple decimals split into multiple numbers starting at 2nd decimal. Ex: 1.2.3 = 1.2 and .3
            Longs and Doubles cannot be add/sub/mul/div/mod by the other or compared
            Functinos and comparisons use symbols like '+' and '=' whenever possible, except 'not'

        ##### Nil

            Stored as separate nil typed atoms
            Input as '()'. Inputing nil creates a symbol atom, not nil
            Prints out as '()'

        ##### True/false

            True is output as 't, but all non nil are considered truthy
            False is nil

        ##### Functions

            Must have correct number of args as defined
            Can be defined to a symbol with 'define' or a lambda function bound to a symbol with 'set'
            Function names must be symbols. Might be possible to set key to string or other but calling won't work
            Able to overwrite predefined functions
        
        ##### Environment

            Looking up unbound symbol returns the looked up symbol
            Variables and functions stored in same environment. Functions stored as lambda functions
            Only use symbols as keys. 'set' seems to work with other atom types as keys but looking up does not work.
            New environment created for each function call to add arguments. Can be an issue, create lots of envs in deep recursive calls.

        ##### Eval

            Everything gets eval() unless quoted or in certain circumstances like defining a function
            All function arguments get evaluated unless quoted
            Function calls given new environment with parent env and args

        ##### Errors
        
            Errors return a string SExp that breifly describes the error. Ex: "Not numbers" when adding a SExp that isn't a number.
            Used for anything that would create unknown outcome such as (set x) which sets x to nothing
            Can be annoying because errors count as true since they're strings