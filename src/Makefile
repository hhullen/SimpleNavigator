MAIN_PROJ_NAME=SimpleNavigator
TEST_DIR=tests
GRAPH_DIR=graph
ALGORITHMS_DIR=algorithms
INCLUDE_DIR=include
GRAPH_BUILD_FILES=$(GRAPH_DIR)$(SEP)graph.cc
ALGORITHMS_BUILD_FILES=$(ALGORITHMS_DIR)$(SEP)graph_algorithms.cc
TESTBUILD_FILES=$(TEST_DIR)$(SEP)$(MAIN_PROJ_NAME)_tests.cc
EXECUTABLE=$(MAIN_PROJ_NAME)_test.out
COMPILER=g++
STD=--std=c++17
CODE_DIAG_FLAGS=-Wall -Wextra -Werror -Wpedantic
TEST_FLAGS=-lgtest -pthread -lgtest_main
CLANG_FILE=.clang-format
CLANG_FILE_WAY=..$(SEP)materials$(SEP)linters$(SEP)$(CLANG_FILE)
CHECK_FILES=$(GRAPH_DIR)$(SEP)* $(ALGORITHMS_DIR)$(SEP)*
CPPCH_SETUP=--enable=warning,performance,portability -v --language=c++ $(STD)
BUILD_DIR=..$(SEP)build
TO_DELETE_FILES=*.o *.out *.dSYM *.gch .DS_Store $(EXECUTABLE) $(CLANG_FILE) \
				dot_test.dot libs21_graph.a libs21_graph_algorithms.a libdot.a
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

all: clean tests

s21_graph.a:
	$(COMPILER) $(STD) $(CODE_DIAG_FLAGS) -c $(GRAPH_BUILD_FILES) -I $(INCLUDE_DIR)
	ar cr libs21_graph.a *.o
	ranlib libs21_graph.a
	$(DELETE_FILE) *.o

s21_graph_algorithms.a:
	$(COMPILER) $(STD) $(CODE_DIAG_FLAGS) -c $(ALGORITHMS_BUILD_FILES) -I $(INCLUDE_DIR)
	ar cr libs21_graph_algorithms.a *.o
	ranlib libs21_graph_algorithms.a
	$(DELETE_FILE) *.o

dotlib.a:
	$(COMPILER) $(STD) $(CODE_DIAG_FLAGS) -c $(INCLUDE_DIR)$(SEP)dot_writer/*.cpp
	ar cr libdot.a *.o
	ranlib libdot.a
	$(DELETE_FILE) *.o

check:
	cppcheck $(CPPCH_SETUP) $(CHECK_FILES)
	$(COPY) $(CLANG_FILE_WAY) $(CLANG_FILE)
	clang-format -i --style=Google $(CHECK_FILES)
	clang-format -n --style=Google $(CHECK_FILES)

tests: dotlib.a s21_graph.a s21_graph_algorithms.a
	$(COMPILER) $(STD) $(CODE_DIAG_FLAGS) $(TESTBUILD_FILES) $(TEST_FLAGS) -I $(INCLUDE_DIR) -L. -ldot -ls21_graph -ls21_graph_algorithms -o $(EXECUTABLE)
	.$(SEP)$(EXECUTABLE)

clean:
	$(DELETE_FOLDER) $(TO_DELETE_FOLDERS)
	$(DELETE_FILE) $(TO_DELETE_FILES)
