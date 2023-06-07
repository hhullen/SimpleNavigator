MAIN_PROJ_NAME=SimpleNavigator
TEST_DIR=tests
GRAPH_DIR=graph
ALGORITHMS_DIR=algorithms
CLI_DIR=utility_cli
INCLUDE_DIR=include
GRAPH_BUILD_FILES=$(GRAPH_DIR)$(SEP)graph.cc
ALGORITHMS_BUILD_FILES=$(ALGORITHMS_DIR)$(SEP)*.cc \
					   $(ALGORITHMS_DIR)$(SEP)tsp_algorithm$(SEP)*.cc
TESTBUILD_FILES=$(TEST_DIR)$(SEP)$(MAIN_PROJ_NAME)_tests.cc
CLI_BULD_FILES=$(CLI_DIR)$(SEP)utility_cli.cc
TEST_EXECUTABLE=$(MAIN_PROJ_NAME)_test.out
CLI_EXECUTABLE=nav
ALGORITHMS_LIB=s21_graph_algorithms
GRAPH_LIB=s21_graph
LIBS_TO_COMPILE=-L. -l$(DOT_LIB) -l$(GRAPH_LIB) -l$(ALGORITHMS_LIB)
DOT_LIB=dotlib
COMPILER=g++
STD=--std=c++17
CODE_DIAG_FLAGS=-Wall -Wextra -Werror -Wpedantic
TEST_FLAGS=-lgtest -pthread -lgtest_main
CLANG_FILE=.clang-format
CLANG_FILE_WAY=..$(SEP)materials$(SEP)linters$(SEP)$(CLANG_FILE)
CHECK_FILES=$(GRAPH_DIR)$(SEP)* $(ALGORITHMS_DIR)$(SEP)*.* \
			$(ALGORITHMS_DIR)$(SEP)tsp_algorithm$(SEP)*.* \
			$(CLI_DIR)$(SEP)*
CPPCH_SETUP=--enable=all --suppress=missingInclude --suppress=unusedFunction -v --language=c++ $(STD)
BUILD_DIR=..$(SEP)build
TO_DELETE_FILES=*.o *.out *.dSYM *.gch *.gcda *.gcno .DS_Store $(TEST_EXECUTABLE) $(CLI_EXECUTABLE) $(CLANG_FILE) \
				*.info dot_test.dot lib$(GRAPH_LIB).a lib$(ALGORITHMS_LIB).a lib$(DOT_LIB).a
TO_DELETE_FOLDERS=$(BUILD_DIR) report

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

all: clean tests nav_cli check

$(GRAPH_LIB).a: libs21_graph.a

libs21_graph.a:
	$(COMPILER) $(STD) $(CODE_DIAG_FLAGS) -O3 -c $(GRAPH_BUILD_FILES) -I $(INCLUDE_DIR)
	ar cr lib$(GRAPH_LIB).a *.o
	ranlib lib$(GRAPH_LIB).a
	$(DELETE_FILE) *.o

$(ALGORITHMS_LIB).a: libs21_graph_algorithms.a

libs21_graph_algorithms.a:
	$(COMPILER) $(STD) $(CODE_DIAG_FLAGS) -O3 -c $(ALGORITHMS_BUILD_FILES) -I $(INCLUDE_DIR)
	ar cr lib$(ALGORITHMS_LIB).a *.o
	ranlib lib$(ALGORITHMS_LIB).a
	$(DELETE_FILE) *.o

$(DOT_LIB).a: libdotlib.a

libdotlib.a:
	$(COMPILER) $(STD) $(CODE_DIAG_FLAGS) -O3 -c $(INCLUDE_DIR)$(SEP)dot_writer$(SEP)*.cpp
	ar cr lib$(DOT_LIB).a *.o
	ranlib lib$(DOT_LIB).a
	$(DELETE_FILE) *.o

check:
	cppcheck $(CPPCH_SETUP) $(CHECK_FILES)
	$(COPY) $(CLANG_FILE_WAY) $(CLANG_FILE)
	clang-format -i --style=Google $(CHECK_FILES)
	clang-format -n --style=Google $(CHECK_FILES)

tests: $(DOT_LIB).a $(GRAPH_LIB).a $(ALGORITHMS_LIB).a
	$(COMPILER) $(STD) $(TESTBUILD_FILES) $(CLI_BULD_FILES) $(TEST_FLAGS) \
	-I $(INCLUDE_DIR) $(LIBS_TO_COMPILE) -o $(TEST_EXECUTABLE)
	.$(SEP)$(TEST_EXECUTABLE)

gcov_report: gcov_build
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info

gcov_build: $(DOT_LIB).a
	$(COMPILER) $(STD) $(TESTBUILD_FILES) $(CLI_BULD_FILES) $(GRAPH_BUILD_FILES) \
	$(ALGORITHMS_BUILD_FILES) -I $(INCLUDE_DIR) -L. -l$(DOT_LIB) $(TEST_FLAGS) \
	-o $(TEST_EXECUTABLE) --coverage
	.$(SEP)$(TEST_EXECUTABLE)

clean:
	$(DELETE_FOLDER) $(TO_DELETE_FOLDERS)
	$(DELETE_FILE) $(TO_DELETE_FILES)

nav_cli: libdotlib.a libs21_graph.a libs21_graph_algorithms.a
	$(MAKEDIR) -p $(BUILD_DIR)
	g++ $(STD) -O3 -o $(BUILD_DIR)$(SEP)$(CLI_EXECUTABLE) main.cc $(CLI_BULD_FILES) $(LIBS_TO_COMPILE)  -I $(INCLUDE_DIR)
	.$(SEP)$(BUILD_DIR)$(SEP)$(CLI_EXECUTABLE) -f tests$(SEP)graph_example.txt -m DFS -s 4
	.$(SEP)$(BUILD_DIR)$(SEP)$(CLI_EXECUTABLE) -f tests$(SEP)graph_example.txt -m BFS -s 9
	.$(SEP)$(BUILD_DIR)$(SEP)$(CLI_EXECUTABLE) -f tests$(SEP)graph_example.txt -m SPBV -s 7 -e 1
	.$(SEP)$(BUILD_DIR)$(SEP)$(CLI_EXECUTABLE) -f tests$(SEP)graph_example.txt -m SPBA
	.$(SEP)$(BUILD_DIR)$(SEP)$(CLI_EXECUTABLE) -f tests$(SEP)graph_example.txt -m LST
	.$(SEP)$(BUILD_DIR)$(SEP)$(CLI_EXECUTABLE) -f tests$(SEP)graph_example.txt -m TSP
	.$(SEP)$(BUILD_DIR)$(SEP)$(CLI_EXECUTABLE) -f tests$(SEP)graph_example.txt -o dot_test.dot
