CXX = g++
CXXFLAGS = -std=c++23 -I./src
BUILD_DIR = build

SRC_FILES = \
    src/types/atom.cpp \
    src/types/cons.cpp \
    src/types/s_expression.cpp \
    src/types/token.cpp \
    src/input/reader.cpp \
    src/input/scanner.cpp \
    src/input/parser.cpp \
    src/core/eval.cpp \
    src/core/environment.cpp \
    src/core/type_checker.cpp \
    src/core/conditional.cpp \
    src/core/number_function.cpp \
    src/core/logical_function.cpp \
    src/util/logger.cpp

TEST_FILES = \
    tests/input/reader_test.cpp \
    tests/input/scanner_test.cpp \
    tests/types/atom_test.cpp \
    tests/types/cons_test.cpp \
    tests/types/sexp_test.cpp \
    tests/core/environment_test.cpp \
    tests/core/type_checker_test.cpp \
    tests/core/number_function_test.cpp \
    tests/core/logical_function_test.cpp \
    tests/core/conditional_test.cpp

all: $(BUILD_DIR)/main.exe $(BUILD_DIR)/tests_main.exe

$(BUILD_DIR)/main.exe: src/main.cpp $(SRC_FILES) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ src/main.cpp $(SRC_FILES)

$(BUILD_DIR)/tests_main.exe: tests/main.cpp $(SRC_FILES) $(TEST_FILES) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ tests/main.cpp $(SRC_FILES) $(TEST_FILES)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf build/*

.PHONY: all clean