#include <gtest/gtest.h>

#include "../graph/graph.h"

using s21::Graph;
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