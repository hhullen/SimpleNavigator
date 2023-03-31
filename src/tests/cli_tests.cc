#include <gtest/gtest.h>

#include "../utility_cli/utility_cli.h"

using s21::UtilityCLI;
using std::invalid_argument;

TEST(cli_tests, constructor_with_args) {
  int argc = 5;
  vector<char *> argv(argc);
  argv[0] = string("nav").data();
  argv[1] = string("-f").data();
  argv[2] = string("tests/graph_example.txt").data();
  argv[3] = string("-m").data();
  argv[4] = string("TSP").data();
  // char *argv[] = {"nav", "-f", "tests/graph_example.txt", "-m", "TSP"};
  EXPECT_NO_THROW(UtilityCLI cli(argc, argv.data()));
}

TEST(cli_tests, constructor_no_args) {
  int argc = 1;
  vector<char *> argv(argc);
  argv[0] = string("nav").data();
  EXPECT_NO_THROW(UtilityCLI cli(argc, argv.data()));
}

TEST(cli_tests, constructor_option_with_no_parameter) {
  int argc = 2;
  vector<char *> argv(argc);
  argv[0] = string("nav").data();
  argv[1] = string("-f").data();
  EXPECT_THROW(UtilityCLI cli(argc, argv.data()), invalid_argument);
}

TEST(cli_tests, constructor_option_with_options_in_a_row) {
  int argc = 5;
  vector<char *> argv(argc);
  argv[0] = string("nav").data();
  argv[1] = string("-f").data();
  argv[2] = string("-m").data();
  argv[3] = string("-s").data();
  argv[4] = string("-e").data();
  EXPECT_THROW(UtilityCLI cli(argc, argv.data()), invalid_argument);
}

TEST(cli_tests, execution_wrong_mode) {
  int argc = 5;
  vector<char *> argv(argc);
  argv[0] = string("nav").data();
  argv[1] = string("-f").data();
  argv[2] = string("tests/graph_example.txt").data();
  argv[3] = string("-m").data();
  argv[4] = string("ABOBA").data();
  UtilityCLI cli(argc, argv.data());
  EXPECT_THROW(cli.Exec(), invalid_argument);
}

TEST(cli_tests, execution_with_no_options) {
  int argc = 1;
  vector<char *> argv(argc);
  argv[0] = string("nav").data();
  UtilityCLI cli(argc, argv.data());
  EXPECT_THROW(cli.Exec(), invalid_argument);
}

TEST(cli_tests, execution_DFS) {
  int argc = 7;
  vector<char *> argv(argc);
  argv[0] = string("nav").data();
  argv[1] = string("-f").data();
  argv[2] = string("tests/graph_example.txt").data();
  argv[3] = string("-m").data();
  argv[4] = string("DFS").data();
  argv[5] = string("-s").data();
  argv[6] = string("4").data();
  UtilityCLI cli(argc, argv.data());
  EXPECT_NO_THROW(cli.Exec());
}

TEST(cli_tests, execution_DFS_overwhelmed_vertex_value) {
  int argc = 7;
  vector<char *> argv(argc);
  argv[0] = string("nav").data();
  argv[1] = string("-f").data();
  argv[2] = string("tests/graph_example.txt").data();
  argv[3] = string("-m").data();
  argv[4] = string("DFS").data();
  argv[5] = string("-s").data();
  argv[6] = string("60").data();
  UtilityCLI cli(argc, argv.data());
  EXPECT_THROW(cli.Exec(), invalid_argument);
}

TEST(cli_tests, execution_DFS_negative_vertex_value) {
  int argc = 7;
  vector<char *> argv(argc);
  argv[0] = string("nav").data();
  argv[1] = string("-f").data();
  argv[2] = string("tests/graph_example.txt").data();
  argv[3] = string("-m").data();
  argv[4] = string("DFS").data();
  argv[5] = string("-s").data();
  argv[6] = string("-60").data();
  UtilityCLI cli(argc, argv.data());
  EXPECT_THROW(cli.Exec(), invalid_argument);
}

TEST(cli_tests, execution_BFS) {
  int argc = 7;
  vector<char *> argv(argc);
  argv[0] = string("nav").data();
  argv[1] = string("-f").data();
  argv[2] = string("tests/graph_example.txt").data();
  argv[3] = string("-m").data();
  argv[4] = string("BFS").data();
  argv[5] = string("-s").data();
  argv[6] = string("4").data();
  UtilityCLI cli(argc, argv.data());
  EXPECT_NO_THROW(cli.Exec());
}

TEST(cli_tests, execution_BFS_overwhelmed_vertex_value) {
  int argc = 7;
  vector<char *> argv(argc);
  argv[0] = string("nav").data();
  argv[1] = string("-f").data();
  argv[2] = string("tests/graph_example.txt").data();
  argv[3] = string("-m").data();
  argv[4] = string("BFS").data();
  argv[5] = string("-s").data();
  argv[6] = string("60").data();
  UtilityCLI cli(argc, argv.data());
  EXPECT_THROW(cli.Exec(), invalid_argument);
}

TEST(cli_tests, execution_BFS_negative_vertex_value) {
  int argc = 7;
  vector<char *> argv(argc);
  argv[0] = string("nav").data();
  argv[1] = string("-f").data();
  argv[2] = string("tests/graph_example.txt").data();
  argv[3] = string("-m").data();
  argv[4] = string("BFS").data();
  argv[5] = string("-s").data();
  argv[6] = string("-60").data();
  UtilityCLI cli(argc, argv.data());
  EXPECT_THROW(cli.Exec(), invalid_argument);
}

TEST(cli_tests, execution_SPBV) {
  int argc = 9;
  vector<char *> argv(argc);
  argv[0] = string("nav").data();
  argv[1] = string("-f").data();
  argv[2] = string("tests/graph_example.txt").data();
  argv[3] = string("-m").data();
  argv[4] = string("SPBV").data();
  argv[5] = string("-s").data();
  argv[6] = string("4").data();
  argv[7] = string("-e").data();
  argv[8] = string("9").data();
  UtilityCLI cli(argc, argv.data());
  EXPECT_NO_THROW(cli.Exec());
}

TEST(cli_tests, execution_SPBV_overwhelmed_vertex_value) {
  int argc = 9;
  vector<char *> argv(argc);
  argv[0] = string("nav").data();
  argv[1] = string("-f").data();
  argv[2] = string("tests/graph_example.txt").data();
  argv[3] = string("-m").data();
  argv[4] = string("SPBV").data();
  argv[5] = string("-s").data();
  argv[6] = string("430").data();
  argv[7] = string("-e").data();
  argv[8] = string("900").data();
  UtilityCLI cli(argc, argv.data());
  EXPECT_THROW(cli.Exec(), invalid_argument);
}

TEST(cli_tests, execution_SPBV_negative_vertex_value) {
  int argc = 9;
  vector<char *> argv(argc);
  argv[0] = string("nav").data();
  argv[1] = string("-f").data();
  argv[2] = string("tests/graph_example.txt").data();
  argv[3] = string("-m").data();
  argv[4] = string("SPBV").data();
  argv[5] = string("-s").data();
  argv[6] = string("-3").data();
  argv[7] = string("-e").data();
  argv[8] = string("7").data();
  UtilityCLI cli(argc, argv.data());
  EXPECT_THROW(cli.Exec(), invalid_argument);
}

TEST(cli_tests, execution_SPBV_no_end_vertex) {
  int argc = 7;
  vector<char *> argv(argc);
  argv[0] = string("nav").data();
  argv[1] = string("-f").data();
  argv[2] = string("tests/graph_example.txt").data();
  argv[3] = string("-m").data();
  argv[4] = string("SPBV").data();
  argv[5] = string("-s").data();
  argv[6] = string("3").data();
  UtilityCLI cli(argc, argv.data());
  EXPECT_THROW(cli.Exec(), invalid_argument);
}

TEST(cli_tests, execution_SPBA) {
  int argc = 5;
  vector<char *> argv(argc);
  argv[0] = string("nav").data();
  argv[1] = string("-f").data();
  argv[2] = string("tests/graph_example.txt").data();
  argv[3] = string("-m").data();
  argv[4] = string("SPBA").data();
  UtilityCLI cli(argc, argv.data());
  EXPECT_NO_THROW(cli.Exec());
}

TEST(cli_tests, execution_TSP) {
  int argc = 5;
  vector<char *> argv(argc);
  argv[0] = string("nav").data();
  argv[1] = string("-f").data();
  argv[2] = string("tests/graph_example.txt").data();
  argv[3] = string("-m").data();
  argv[4] = string("TSP").data();
  UtilityCLI cli(argc, argv.data());
  EXPECT_NO_THROW(cli.Exec());
}

TEST(cli_tests, execution_LST) {
  int argc = 5;
  vector<char *> argv(argc);
  argv[0] = string("nav").data();
  argv[1] = string("-f").data();
  argv[2] = string("tests/graph_example.txt").data();
  argv[3] = string("-m").data();
  argv[4] = string("LST").data();
  UtilityCLI cli(argc, argv.data());
  EXPECT_NO_THROW(cli.Exec());
}

TEST(cli_tests, execution_out_file) {
  int argc = 5;
  vector<char *> argv(argc);
  argv[0] = string("nav").data();
  argv[1] = string("-f").data();
  argv[2] = string("tests/graph_example.txt").data();
  argv[3] = string("-o").data();
  argv[4] = string("dot_test.dot").data();
  UtilityCLI cli(argc, argv.data());
  EXPECT_NO_THROW(cli.Exec());
}
