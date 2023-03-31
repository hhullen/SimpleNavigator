MAIN_PROJ_NAME=SimpleNavigator
TEST_DIR=tests
GRAPH_DIR=graph
ALGORITHMS_DIR=algorithms
INCLUDE_DIR=include
GRAPH_BUILD_FILES=$(GRAPH_DIR)$(SEP)graph.cc
ALGORITHMS_BUILD_FILES=$(ALGORITHMS_DIR)$(SEP)graph_algorithms.cc
TESTBUILD_FILES=$(TEST_DIR)$(SEP)$(MAIN_PROJ_NAME)_tests.cc
EXECUTABLE=$(MAIN_PROJ_NAME)_test.out
ALGORITHMS_LIB=s21_graph_algorithms
GRAPH_LIB=s21_graph
DOT_LIB=dotlib
COMPILER=g++
STD=--std=c++17
CODE_DIAG_FLAGS=-Wall -Wextra -Werror -Wpedantic
TEST_FLAGS=-lgtest -pthread -lgtest_main
CLANG_FILE=.clang-format
CLANG_FILE_WAY=..$(SEP)materials$(SEP)linters$(SEP)$(CLANG_FILE)
CHECK_FILES=$(GRAPH_DIR)$(SEP)* $(ALGORITHMS_DIR)$(SEP)*
CPPCH_SETUP=--enable=all --suppress=missingInclude --suppress=unusedFunction -v --language=c++ $(STD)
BUILD_DIR=..$(SEP)build
TO_DELETE_FILES=*.o *.out *.dSYM *.gch .DS_Store $(EXECUTABLE) $(CLANG_FILE) \
				dot_test.dot lib$(GRAPH_LIB).a lib$(ALGORITHMS_LIB).a lib$(DOT_LIB).a
TO_DELETE_FOLDERS=$(BUILD_DIR)

#Crossplatform specs
SEP='\'
MAKEDIR=md
DELETE_FOLDER=RD /S/Q
DELETE_FILE=DEL /F
COPY=copy
OPEN=start
OS=$(shell uname)

ifeq ($(OS), Linux)
	OPEN=xdg-open
	MAKEDIR=mkdir -p
	SEP=/
	DELETE_FOLDER=rm -rf
	DELETE_FILE=rm -f
	COPY=cp
endif

ifeq ($(OS), Darwin)
	OPEN=open
	MAKEDIR=mkdir -p
	SEP=/
	DELETE_FOLDER=rm -rf
	DELETE_FILE=rm -f
	COPY=cp
endif

.PHONY: all check tests clean

all: clean tests

$(GRAPH_LIB).a:
	$(COMPILER) $(STD) $(CODE_DIAG_FLAGS) -c $(GRAPH_BUILD_FILES) -I $(INCLUDE_DIR)
	ar cr lib$(GRAPH_LIB).a *.o
	ranlib lib$(GRAPH_LIB).a
	$(DELETE_FILE) *.o

$(ALGORITHMS_LIB).a:
	$(COMPILER) $(STD) $(CODE_DIAG_FLAGS) -c $(ALGORITHMS_BUILD_FILES) -I $(INCLUDE_DIR)
	ar cr lib$(ALGORITHMS_LIB).a *.o
	ranlib lib$(ALGORITHMS_LIB).a
	$(DELETE_FILE) *.o

$(DOT_LIB).a:
	$(COMPILER) $(STD) $(CODE_DIAG_FLAGS) -c $(INCLUDE_DIR)$(SEP)dot_writer/*.cpp
	ar cr lib$(DOT_LIB).a *.o
	ranlib lib$(DOT_LIB).a
	$(DELETE_FILE) *.o

check:
	cppcheck $(CPPCH_SETUP) $(CHECK_FILES)
	$(COPY) $(CLANG_FILE_WAY) $(CLANG_FILE)
	clang-format -i --style=Google $(CHECK_FILES)
	clang-format -n --style=Google $(CHECK_FILES)

tests: $(DOT_LIB).a $(GRAPH_LIB).a $(ALGORITHMS_LIB).a
	$(COMPILER) $(STD) -O3 $(CODE_DIAG_FLAGS) $(TESTBUILD_FILES) $(TEST_FLAGS) \
	-I $(INCLUDE_DIR) -L. -l$(DOT_LIB) -l$(GRAPH_LIB) -l$(ALGORITHMS_LIB) -o $(EXECUTABLE)
	.$(SEP)$(EXECUTABLE)

clean:
	$(DELETE_FOLDER) $(TO_DELETE_FOLDERS)
	$(DELETE_FILE) $(TO_DELETE_FILES)
