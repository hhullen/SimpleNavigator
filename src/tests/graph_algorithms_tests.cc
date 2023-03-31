#include <gtest/gtest.h>

#include <string>

#include "../algorithms/graph_algorithms.h"
#include "../graph/graph.h"

using s21::Graph;
using s21::GraphAlgorithms;
using std::invalid_argument;
using std::string;

TEST(algorithms_tests, constructor) {
  EXPECT_NO_THROW(GraphAlgorithms algorithm);
}

TEST(algorithms_tests, DFS) {
  GraphAlgorithms algorithm;
  Graph graph;
  string file = "tests/graph_example.txt";
  graph.LoadGraphFromFile(file);
  EXPECT_NO_THROW(algorithm.depthFirstSearch(graph, 1));
}

TEST(algorithms_tests, DFS_overwhelmed_vertex_value) {
  GraphAlgorithms algorithm;
  Graph graph;
  string file = "tests/graph_example.txt";
  graph.LoadGraphFromFile(file);
  EXPECT_THROW(algorithm.depthFirstSearch(graph, 150), invalid_argument);
}

TEST(algorithms_tests, DFS_negative_vertex_value) {
  GraphAlgorithms algorithm;
  Graph graph;
  string file = "tests/graph_example.txt";
  graph.LoadGraphFromFile(file);
  EXPECT_THROW(algorithm.depthFirstSearch(graph, -3), invalid_argument);
}

TEST(algorithms_tests, BFS) {
  GraphAlgorithms algorithm;
  Graph graph;
  string file = "tests/graph_example.txt";
  graph.LoadGraphFromFile(file);
  EXPECT_NO_THROW(algorithm.breadthFirstSearch(graph, 1));
}

TEST(algorithms_tests, BFS_overwhelmed_vertex_value) {
  GraphAlgorithms algorithm;
  Graph graph;
  string file = "tests/graph_example.txt";
  graph.LoadGraphFromFile(file);
  EXPECT_THROW(algorithm.breadthFirstSearch(graph, 150), invalid_argument);
}

TEST(algorithms_tests, BFS_negative_vertex_value) {
  GraphAlgorithms algorithm;
  Graph graph;
  string file = "tests/graph_example.txt";
  graph.LoadGraphFromFile(file);
  EXPECT_THROW(algorithm.breadthFirstSearch(graph, -3), invalid_argument);
}

TEST(algorithms_tests, SPBV) {
  GraphAlgorithms algorithm;
  Graph graph;
  string file = "tests/graph_example.txt";
  graph.LoadGraphFromFile(file);
  EXPECT_NO_THROW(algorithm.getShortestPathBetweenVertices(graph, 1, 9));
}

TEST(algorithms_tests, SPBV_overwhelmed_first_vertex_value) {
  GraphAlgorithms algorithm;
  Graph graph;
  string file = "tests/graph_example.txt";
  graph.LoadGraphFromFile(file);
  EXPECT_THROW(algorithm.getShortestPathBetweenVertices(graph, 2, 150),
               invalid_argument);
}

TEST(algorithms_tests, SPBV_overwhelmed_second_vertex_value) {
  GraphAlgorithms algorithm;
  Graph graph;
  string file = "tests/graph_example.txt";
  graph.LoadGraphFromFile(file);
  EXPECT_THROW(algorithm.getShortestPathBetweenVertices(graph, 200, 1),
               invalid_argument);
}

TEST(algorithms_tests, SPBV_negative_first_vertex_value) {
  GraphAlgorithms algorithm;
  Graph graph;
  string file = "tests/graph_example.txt";
  graph.LoadGraphFromFile(file);
  EXPECT_THROW(algorithm.getShortestPathBetweenVertices(graph, -3, 4),
               invalid_argument);
}

TEST(algorithms_tests, SPBV_negative_second_vertex_value) {
  GraphAlgorithms algorithm;
  Graph graph;
  string file = "tests/graph_example.txt";
  graph.LoadGraphFromFile(file);
  EXPECT_THROW(algorithm.getShortestPathBetweenVertices(graph, 3, -4),
               invalid_argument);
}

TEST(algorithms_tests, SPBA) {
  GraphAlgorithms algorithm;
  Graph graph;
  string file = "tests/graph_example.txt";
  graph.LoadGraphFromFile(file);
  EXPECT_NO_THROW(algorithm.getShortestPathsBetweenAllVertices(graph));
}

TEST(algorithms_tests, TSP) {
  GraphAlgorithms algorithm;
  Graph graph;
  string file = "tests/graph_example.txt";
  graph.LoadGraphFromFile(file);
  EXPECT_NO_THROW(algorithm.solveTravelingSalesmanProblem(graph));
}

TEST(algorithms_tests, LST) {
  GraphAlgorithms algorithm;
  Graph graph;
  string file = "tests/graph_example.txt";
  graph.LoadGraphFromFile(file);
  EXPECT_NO_THROW(algorithm.getLeastSpanningTree(graph));
}

TEST(algorithms_tests, INC_LST) {
  GraphAlgorithms algorithm;
  Graph graph;
  string file = "tests/graph_example_bad_graph.txt";
  graph.LoadGraphFromFile(file);
  EXPECT_THROW(algorithm.getLeastSpanningTree(graph), invalid_argument);
}