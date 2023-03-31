#include "graph_algorithms.h"

namespace s21 {

GraphAlgorithms::GraphAlgorithms() {}

vector<int> GraphAlgorithms::depthFirstSearch(Graph &graph, int startVertex) {
  Validatevertex(graph, startVertex);
  vector<int> result;
  vector<bool> visited;
  stack<int> stack_vertex;
  int pop_vertex = 0;
  int matrix_size = graph.get_size();
  visited.resize(matrix_size);
  stack_vertex.push(startVertex - 1);
  while (!stack_vertex.empty()) {
    pop_vertex = stack_vertex.top();
    stack_vertex.pop();
    if (!visited[pop_vertex]) {
      visited[pop_vertex] = 1;
      for (int i = matrix_size - 1; i >= 0; --i) {
        if (graph(pop_vertex, i) && !visited[i]) {
          stack_vertex.push(i);
        }
      }
      result.push_back(pop_vertex + 1);
    }
  }
  return result;
}

vector<int> GraphAlgorithms::breadthFirstSearch(Graph &graph, int startVertex) {
  Validatevertex(graph, startVertex);
  vector<int> result;
  vector<bool> visited;
  queue<int> queue_vertex;
  int matrix_size = graph.get_size();
  visited.resize(matrix_size);
  queue_vertex.push(startVertex - 1);
  int pop_vertex = 0;
  while (!queue_vertex.empty()) {
    pop_vertex = queue_vertex.front();
    queue_vertex.pop();
    if (!visited[pop_vertex]) {
      visited[pop_vertex] = 1;
      for (int i = 0; i < matrix_size; ++i) {
        if (graph(pop_vertex, i) && !visited[i]) {
          queue_vertex.push(i);
        }
      }
      result.push_back(pop_vertex + 1);
    }
  }
  return result;
}

int GraphAlgorithms::getShortestPathBetweenVertices(Graph &graph, int vertex1,
                                                    int vertex2) {
  Validatevertex(graph, vertex1);
  Validatevertex(graph, vertex2);
  vector<bool> visited;
  queue<int> queue_vertex;
  int matrix_size = graph.get_size();
  vector<int> weights(matrix_size, INT_MAX);
  weights[vertex1 - 1] = 0;
  visited.resize(matrix_size);
  queue_vertex.push(vertex1 - 1);
  int pop_vertex = 0;
  while (!queue_vertex.empty()) {
    pop_vertex = queue_vertex.front();
    queue_vertex.pop();
    if (!visited[pop_vertex]) {
      visited[pop_vertex] = 1;
      for (int i = 0; i < matrix_size; ++i) {
        if (graph(pop_vertex, i)) {
          if (weights[i] > weights[pop_vertex] + graph(pop_vertex, i)) {
            weights[i] = weights[pop_vertex] + graph(pop_vertex, i);
          }
          if (!visited[i]) {
            queue_vertex.push(i);
          }
        }
      }
    }
  }
  return weights[vertex2 - 1];
}

Graph GraphAlgorithms::getShortestPathsBetweenAllVertices(Graph &graph) {
  int graph_size = graph.get_size();
  Graph result(graph_size);
  result = graph;
  for (int k = 0; k < graph_size; ++k) {
    for (int i = 0; i < graph_size; ++i) {
      for (int j = 0; j < graph_size; ++j) {
        if (result(i, k) && result(k, j) && i != j) {
          if (result(i, j) > result(i, k) + result(k, j) || result(i, j) == 0) {
            result(i, j) = result(i, k) + result(k, j);
          }
        }
      }
    }
  }
  return result;
}

std::vector<std::vector<int>>
GraphAlgorithms::getLeastSpanningTree(Graph &graph) {
  int graph_size = graph.get_size();
  vector<bool> visited;
  visited.resize(graph_size);
  visited[0] = 0;
  std::vector<int> path(graph_size, -1);
  std::vector<int> min(graph_size, INT_MAX);
  min[0] = 0;
  Graph tmp = graph;
  std::vector<std::vector<int>> res(graph_size, std::vector<int>(graph_size));
  for (int i = 0; i < graph_size; ++i) {
    for (int j = 0; j < graph_size; ++j) {
      if (i != j && tmp(i, j) == 0) {
        tmp(i, j) = INT_MAX;
      }
    }
  }
  for (int i = 0; i < graph_size; ++i) {
    int vert = -1;
    for (int j = 0; j < graph_size; ++j) {
      if (!visited.at(j) && (vert == -1 || min[j] < min[vert])) {
        vert = j;
      }
    }
    if (min[vert] == INT_MAX) {
      throw invalid_argument("Incorrect graph");
    }
    visited.at(vert) = true;
    if (path.at(vert) != -1) {
      res[path.at(vert)][vert] = tmp(path.at(vert), vert);
      res[vert][path.at(vert)] = tmp(vert, path.at(vert));
    }
    for (int k = 0; k < graph_size; ++k) {
      if (tmp(vert, k) < min[k]) {
        min[k] = tmp(vert, k);
        path.at(k) = vert;
      }
    }
  }
  return res;
}

TsmResult GraphAlgorithms::solveTravelingSalesmanProblem(Graph &graph) {
  TSPAlgorithm tsp;
  return tsp.Solve(graph);
}

void GraphAlgorithms::Validatevertex(Graph &graph, int vertex) {
  if (vertex < 1 || static_cast<size_t>(vertex) > graph.get_size()) {
    throw invalid_argument("Incorrect vertex value.");
  }
}

} // namespace s21
