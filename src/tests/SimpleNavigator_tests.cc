#include <gtest/gtest.h>

#include "../algorithms/graph_algorithms.h"
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
  EXPECT_EQ(gg.get_size(), 6);
}

TEST(graph_tests, dot_exporting) {
  Graph gg;
  EXPECT_THROW(gg.ExportGraphToDot(""), invalid_argument);
  gg.LoadGraphFromFile("tests/graph_example.txt");
  EXPECT_NO_THROW(gg.ExportGraphToDot("dot_test.dot"));
}

TEST(biba, boba) {
  s21::Graph graph;
  s21::Graph res_graph;
  graph.LoadGraphFromFile("tests/graph_example.txt");
  s21::GraphAlgorithms test_algo;
  // res_graph = test_algo.getShortestPathsBetweenAllVertices(graph);
  // std::cout << test_algo.getShortestPathBetweenVertices(graph, 12, 19);
  std::vector<std::vector<int>> aboba;
  aboba = test_algo.getLeastSpanningTree(graph);
  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 6; ++j) {
      std::cout << aboba[i][j] << " ";
    }
    std::cout << '\n';
  }
  // for (auto i : aboba) {
  //   std::cout << i << " ";
  // }
  // aboba = test_algo.breadthFirstSearch(graph, 2);
  // for (size_t i = 0; i < res_graph.get_size(); ++i) {
  //   for (size_t j = 0; j < res_graph.get_size(); ++j) {
  //     std::cout << res_graph(i, j) << ' ';
  //   }
  //   std::cout << '\n';
  // }
  EXPECT_EQ(1, 1);
}