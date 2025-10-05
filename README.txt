1. README

    # Use

        Builds end up in `build` dir.
        Run `main` for use with stdin.
        Run `main < 'filename'` for file as stdin.
        Run `main 'filename'` to read from file. Has similar output as above.

        ### In code

            Logger levels: DEBUG, INFO, WARNING, ERROR, CRITICAL.
                Most used are INFO and ERROR.
                Prints any messages of lowest level set and any of higher priority.

    # Structure

        src dir has the source code and main.cpp
        tests dir has the test code and test main.cpp

    # Building

        ### CMake

            First time, from build dir, need to run `cmake ..`
            From build dir, run `cmake --build .`
            Creates 'main.exe' and 'tests.exe'

            ##### Tests

                From build dir, run `cmake --build . --target <test name>`
                Creates 'tests.exe'

        ### Makefile

            From root dir, run `make`
            Creates 'main.exe' and 'tests_main.exe'

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
            FIXME need to add parser tests but test by hand works and needed for other tests that work.

        ### Types

            Atoms tested by creating and using created atoms
            Cons Cells tested by creating and using cons cells. FIXME add nested list testing but works by hand.
            S Expression tested by creating s expressions with atoms and cons cells.

3. Test output

    # Automatic testing

        *Due to the way I handle input, could not remove the '>' while testing the reader and scanner

        $ ./tests
        INFO: ----- Input handling Tests -----
        > > > > > > > > INFO: PASS: Reader tests passed.
        > > > > > > > > > INFO: PASS: Scanner tests passed.
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
        INFO: PASS: getDouble
        INFO: PASS: getType
        INFO: ----- Cons tests -----
        INFO: PASS: car
        INFO: PASS: cdr
        INFO: PASS: toVector size
        INFO: PASS: car
        INFO: PASS: cdr
        INFO: PASS: toVector size
        INFO: PASS: toVector size
        INFO: PASS: toVector contents
        INFO: ----- SExpression tests -----
        INFO: PASS: atom SExpression getType
        INFO: PASS: cons SExpression getType
        INFO: PASS: atom SExpression getAtom
        INFO: PASS: cons SExpression getCons
        INFO: Tests complete.
        INFO: Passes: 15
        INFO: Fails: 0

    # Manual

        $ ./main
        > 42
        : 42
        > 1.2
        : 1.200000
        > 1.2.3
        : 1.200000
        : 0.300000
        > Hello world
        : Hello
        : world
        > "Roll tide"
        : "Roll tide"
        > (Roll tide)
        : ( Roll tide )
        > ""
        : ""
        > "Hello . world"
        : "Hello . world"
        > "Hello () world"
        : "Hello () world"
        > ("Hello" "World")
        : ( "Hello" "World" )
        > ( (1)
        >  (2)
        >  (3))
        : ( ( 1 ) ( 2 ) ( 3 ) )

4. Documentation

    ### Limitations

        QUOTE and ' not working right now
        Cannot read in dot notation
        Cannot print dot notation after I made a change that broke it

    ### Design Choices

        ##### Symbols

            Start: Currently cannot start with numbers, 1 char keywords, numbers, or a few other special cases like \
            Characters: Currently cannot include single letter keywords like '(' or things like that. But that also includes '.'

        ##### Numbers

            Numbers with multiple decimals split into multiple numbers starting at 2nd decimal. Ex: 1.2.3 = 1.2 and .3
            Longs and Doubles cannot be add/sub/mul/div/mod by the other

        ##### Nil

            Stored as separate nil typed atoms for now. Might change to empty lists later and/or make a singleton for all nils.

        ##### True/false

            True is 't
            False is ()

        ##### Errors
        
            Errors return a string SExp that breifly describes the error. Ex: "Not numbers" when adding a SExp that isn't a number.
        
        ##### Environment

            Looking up unbound symbol returns the looked up symbol