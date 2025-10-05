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

    # Manual


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