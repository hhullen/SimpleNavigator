#include "tsp_algorithm.h"

namespace s21 {

TsmResult TSPAlgorithm::Solve(Graph &graph) {
  size_t size = graph.get_size();
  pheromones_.Resize(size);
  attended_.clear();
  for (size_t i = 0; i < size; ++i) {
    RunThroughGraphFromVertex(graph, i);
  }
  return result_;
}

void TSPAlgorithm::RunThroughGraphFromVertex(Graph &graph, size_t i) {
  size_t size = graph.get_size();
  vector<float> probabilities_;
  float denominator = 0;
  for (size_t j = 0; j < size; ++j) {
    if (!IsAttended(j)) {
      int pheromone = pheromones_(i, j);
      int edge_length = graph(i, j);
      float probability = CalculateNumerator(pheromone, edge_length);
      probabilities_.push_back(probability);
      denominator += probability;
    }
    // attended_.push_back(j);
    // RECURSIVE?????????????????????????
  }
  for (size_t k = 0; k < probabilities_.size(); ++k) {
    probabilities_[k] /= denominator;
  }
}

bool TSPAlgorithm::IsAttended(int j) {
  return find(attended_.begin(), attended_.end(), j) != attended_.end();
}

float TSPAlgorithm::CalculateNumerator(int pheromone, int edge_length) {
  return powf(pheromone, alpha_) + powf(edge_length, beta_);
}

}  // namespace s21
