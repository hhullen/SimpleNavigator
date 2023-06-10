#include <gtest/gtest.h>

#include "../utility_cli/utility_cli.cc"

using s21::UtilityCLI;
using std::invalid_argument;
using std::string;
using std::vector;

TEST(cli_tests, constructor_with_args) {
  int argc = 5;
  vector<const char *> argv({
      "nav",
      "-f",
      "tests/graph_example.txt",
      "-m",
      "TSP",
  });
  EXPECT_NO_THROW(UtilityCLI cli(argc, argv.data()));
}

TEST(cli_tests, constructor_no_args) {
  int argc = 1;
  vector<const char *> argv({"nav"});
  EXPECT_NO_THROW(UtilityCLI cli(argc, argv.data()));
}

TEST(cli_tests, constructor_option_with_no_parameter) {
  int argc = 2;
  vector<const char *> argv({
      "nav",
      "-f",
  });
  EXPECT_THROW(UtilityCLI cli(argc, argv.data()), invalid_argument);
}

TEST(cli_tests, constructor_option_with_options_in_a_row) {
  int argc = 5;
  vector<const char *> argv({
      "nav",
      "-f",
      "-m",
      "-s",
      "-e",
  });

  EXPECT_THROW(UtilityCLI cli(argc, argv.data()), invalid_argument);
}

TEST(cli_tests, execution_wrong_mode) {
  int argc = 5;
  vector<const char *> argv({
      "nav",
      "-f",
      "tests/graph_example.txt",
      "-m",
      "ABOBA",
  });

  UtilityCLI cli(argc, argv.data());
  EXPECT_THROW(cli.Exec(), invalid_argument);
}

TEST(cli_tests, execution_with_no_options) {
  int argc = 1;
  vector<const char *> argv({"nav"});
  UtilityCLI cli(argc, argv.data());
  EXPECT_THROW(cli.Exec(), invalid_argument);
}

TEST(cli_tests, execution_DFS) {
  int argc = 7;
  vector<const char *> argv({
      "nav",
      "-f",
      "tests/graph_example.txt",
      "-m",
      "DFS",
      "-s",
      "4",
  });

  UtilityCLI cli(argc, argv.data());
  EXPECT_NO_THROW(cli.Exec());
}

TEST(cli_tests, execution_DFS_overwhelmed_vertex_value) {
  int argc = 7;
  vector<const char *> argv({
      "nav",
      "-f",
      "tests/graph_example.txt",
      "-m",
      "DFS",
      "-s",
      "60",
  });

  UtilityCLI cli(argc, argv.data());
  EXPECT_THROW(cli.Exec(), invalid_argument);
}

TEST(cli_tests, execution_DFS_negative_vertex_value) {
  int argc = 7;
  vector<const char *> argv({
      "nav",
      "-f",
      "tests/graph_example.txt",
      "-m",
      "DFS",
      "-s",
      "-60",
  });

  UtilityCLI cli(argc, argv.data());
  EXPECT_THROW(cli.Exec(), invalid_argument);
}

TEST(cli_tests, execution_BFS) {
  int argc = 7;
  vector<const char *> argv({
      "nav",
      "-f",
      "tests/graph_example.txt",
      "-m",
      "BFS",
      "-s",
      "4",
  });

  UtilityCLI cli(argc, argv.data());
  EXPECT_NO_THROW(cli.Exec());
}

TEST(cli_tests, execution_BFS_overwhelmed_vertex_value) {
  int argc = 7;
  vector<const char *> argv({
      "nav",
      "-f",
      "tests/graph_example.txt",
      "-m",
      "BFS",
      "-s",
      "60",
  });

  UtilityCLI cli(argc, argv.data());
  EXPECT_THROW(cli.Exec(), invalid_argument);
}

TEST(cli_tests, execution_BFS_negative_vertex_value) {
  int argc = 7;
  vector<const char *> argv({
      "nav",
      "-f",
      "tests/graph_example.txt",
      "-m",
      "BFS",
      "-s",
      "-60",
  });

  UtilityCLI cli(argc, argv.data());
  EXPECT_THROW(cli.Exec(), invalid_argument);
}

TEST(cli_tests, execution_SPBV) {
  int argc = 9;
  vector<const char *> argv({
      "nav",
      "-f",
      "tests/graph_example.txt",
      "-m",
      "SPBV",
      "-s",
      "4",
      "-e",
      "9",
  });

  UtilityCLI cli(argc, argv.data());
  EXPECT_NO_THROW(cli.Exec());
}

TEST(cli_tests, execution_SPBV_overwhelmed_vertex_value) {
  int argc = 9;
  vector<const char *> argv({
      "nav",
      "-f",
      "tests/graph_example.txt",
      "-m",
      "SPBV",
      "-s",
      "430",
      "-e",
      "900",
  });

  UtilityCLI cli(argc, argv.data());
  EXPECT_THROW(cli.Exec(), invalid_argument);
}

TEST(cli_tests, execution_SPBV_negative_vertex_value) {
  int argc = 9;
  vector<const char *> argv({
      "nav",
      "-f",
      "tests/graph_example.txt",
      "-m",
      "SPBV",
      "-s",
      "-3",
      "-e",
      "7",
  });

  UtilityCLI cli(argc, argv.data());
  EXPECT_THROW(cli.Exec(), invalid_argument);
}

TEST(cli_tests, execution_SPBV_no_end_vertex) {
  int argc = 7;
  vector<const char *> argv({
      "nav",
      "-f",
      "tests/graph_example.txt",
      "-m",
      "SPBV",
      "-s",
      "3",
  });

  UtilityCLI cli(argc, argv.data());
  EXPECT_THROW(cli.Exec(), invalid_argument);
}

TEST(cli_tests, execution_SPBA) {
  int argc = 5;
  vector<const char *> argv({
      "nav",
      "-f",
      "tests/graph_example.txt",
      "-m",
      "SPBA",
  });

  UtilityCLI cli(argc, argv.data());
  EXPECT_NO_THROW(cli.Exec());
}

TEST(cli_tests, execution_TSP) {
  int argc = 5;
  vector<const char *> argv({
      "nav",
      "-f",
      "tests/graph_example.txt",
      "-m",
      "TSP",
  });

  UtilityCLI cli(argc, argv.data());
  EXPECT_NO_THROW(cli.Exec());
}

TEST(cli_tests, execution_LST) {
  int argc = 5;
  vector<const char *> argv({
      "nav",
      "-f",
      "tests/graph_example.txt",
      "-m",
      "LST",
  });

  UtilityCLI cli(argc, argv.data());
  EXPECT_NO_THROW(cli.Exec());
}

TEST(cli_tests, execution_out_file) {
  int argc = 5;
  vector<const char *> argv({
      "nav",
      "-f",
      "tests/graph_example.txt",
      "-o",
      "dot_test.dot",
  });

  UtilityCLI cli(argc, argv.data());
  EXPECT_NO_THROW(cli.Exec());
}
