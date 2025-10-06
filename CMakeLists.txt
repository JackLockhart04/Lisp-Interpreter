cmake_minimum_required(VERSION 3.10)
project(lisp_interpreter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

include_directories(src)

set(SRC_FILES
    src/types/atom.cpp
    src/types/cons.cpp
    src/types/s_expression.cpp
    src/types/token.cpp
    src/input/reader.cpp
    src/input/scanner.cpp
    src/input/parser.cpp
    src/core/eval.cpp
    src/core/environment.cpp
    src/core/type_checker.cpp
    src/core/conditional.cpp
    src/core/number_function.cpp
    src/core/logical_function.cpp
    src/util/logger.cpp
)

add_executable(main src/main.cpp ${SRC_FILES})

set(TEST_FILES
    tests/input/reader_test.cpp
    tests/input/scanner_test.cpp
    tests/types/atom_test.cpp
    tests/types/cons_test.cpp
    tests/types/sexp_test.cpp
    tests/core/environment_test.cpp
    tests/core/type_checker_test.cpp
    tests/core/number_function_test.cpp
    tests/core/logical_function_test.cpp
    tests/core/conditional_test.cpp
)

add_executable(tests tests/main.cpp ${SRC_FILES} ${TEST_FILES})