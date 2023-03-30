#include <gtest/gtest.h>

#include "../graph/graph.h"
#include "../utility_cli/utility_cli.h"

using s21::Graph;
using s21::UtilityCLI;
using std::invalid_argument;

TEST(graph_tests, constructing) { EXPECT_NO_THROW(Graph gg); }

TEST(graph_tests, resizing) {
  Graph gg;
  EXPECT_NO_THROW(gg.Resize(1));
  EXPECT_NO_THROW(gg.Resize(13));
  EXPECT_EQ(gg.get_size(), 13);
  EXPECT_THROW(gg.Resize(0), invalid_argument);
  EXPECT_THROW(gg.Resize(-200), invalid_argument);
}

TEST(graph_tests, loading) {
  Graph gg;
  EXPECT_THROW(gg.LoadGraphFromFile(""), invalid_argument);
  EXPECT_THROW(gg.LoadGraphFromFile("tests/graph_example_bad_size.txt"),
               invalid_argument);
  EXPECT_NO_THROW(gg.LoadGraphFromFile("tests/graph_example.txt"));
  EXPECT_EQ(gg.get_size(), 11);
}

TEST(graph_tests, dot_exporting) {
  Graph gg;
  EXPECT_THROW(gg.ExportGraphToDot(""), invalid_argument);
  gg.LoadGraphFromFile("tests/graph_example.txt");
  EXPECT_NO_THROW(gg.ExportGraphToDot("dot_test.dot"));
}

TEST(cli_tests, constructor_with_args) {
  int argc = 5;
  char* argv[] = {"nav", "-f", "tests/graph_example.txt", "-m", "TSP"};
  EXPECT_NO_THROW(UtilityCLI cli(argc, argv));
}

TEST(cli_tests, constructor_no_args) {
  int argc = 1;
  char* argv[] = {"nav"};
  EXPECT_NO_THROW(UtilityCLI cli(argc, argv));
}

TEST(cli_tests, constructor_option_with_no_parameter) {
  int argc = 2;
  char* argv[] = {"nav", "-f"};
  EXPECT_THROW(UtilityCLI cli(argc, argv), invalid_argument);
}

TEST(cli_tests, constructor_option_with_options_in_a_row) {
  int argc = 5;
  char* argv[] = {"nav", "-f", "-m", "-s", "-e"};
  EXPECT_THROW(UtilityCLI cli(argc, argv), invalid_argument);
}

TEST(cli_tests, execution_wrong_mode) {
  int argc = 5;
  char* argv[] = {"nav", "-f", "tests/graph_example.txt", "-m", "ABOBA"};
  UtilityCLI cli(argc, argv);
  EXPECT_THROW(cli.Exec(), invalid_argument);
}

TEST(cli_tests, execution_with_no_options) {
  int argc = 1;
  char* argv[] = {"nav"};
  UtilityCLI cli(argc, argv);
  EXPECT_THROW(cli.Exec(), invalid_argument);
}

TEST(cli_tests, execution_DFS) {
  int argc = 7;
  char* argv[] = {"nav", "-f", "tests/graph_example.txt", "-m", "DFS",
                  "-s",  "4"};
  UtilityCLI cli(argc, argv);
  EXPECT_NO_THROW(cli.Exec());
}

TEST(cli_tests, execution_DFS_wrovg_vertex) {
  int argc = 7;
  char* argv[] = {"nav", "-f", "tests/graph_example.txt", "-m", "DFS",
                  "-s",  "60"};  // SEGA
  UtilityCLI cli(argc, argv);
  EXPECT_NO_THROW(cli.Exec());
}
