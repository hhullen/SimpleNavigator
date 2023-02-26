#include "graph.h"

namespace s21 {
Graph::Graph() {}

Graph::Graph(int size) { Resize(size); }

Graph::Graph(const Graph &other) {}

Graph::~Graph() {
  adjacency_matrix_.clear();
  adjacency_matrix_.shrink_to_fit();
}

int &Graph::operator()(int i, int j) { return adjacency_matrix_[i][j]; }

void Graph::Resize(int size) {
  adjacency_matrix_.resize(size);
  adjacency_matrix_.shrink_to_fit();
  for (vector<int> &row : adjacency_matrix_) {
    row.resize(size);
    row.shrink_to_fit();
  }
}

int Graph::get_size() { return adjacency_matrix_.size(); }

void Graph::LoadGraphFromFile(string &path) {}

void Graph::ExportGraphToDot(string &path) {}

}  // namespace s21
