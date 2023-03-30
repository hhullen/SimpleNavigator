#include "tsp_algorithm.h"

namespace s21 {

TsmResult TSPAlgorithm::Solve(Graph &graph) {
  size_t size = graph.get_size();
  pheromones_.Resize(size);
  attended_.clear();
  for (size_t i = 0; i < size; ++i) {
    attended_.push_back(i);
    RunThroughGraphFromVertex(graph, i);
    attended_.clear();
  }
  return result_;
}

void TSPAlgorithm::RunThroughGraphFromVertex(Graph &graph, size_t start) {
  TsmResult result;
  result.vertices.push_back((int)start);
  result.distance = 0;
  while (IsNotAllAttended(graph)) {
    probabilities_.clear();
    float denominator = GetProbabilitiesDenominator(graph, start);
    DivideProbabilitiesByDenominator(denominator);

    float random_percent = GetRandomPercentValue();
    size_t next_dest = GetNextDestination(random_percent);

    RunPheromonesEvaporation();
    AddPheromoneTrack(start, next_dest);

    result.distance += graph(start, next_dest);
    start = next_dest;
    attended_.push_back(start);
    std::cout << "Random " << random_percent << " NEXT " << start << "\n";
  }
  SetNewResult(result);
  std::cout << "\n";
}

float TSPAlgorithm::GetProbabilitiesDenominator(Graph &graph, size_t start) {
  float denominator = 0;
  for (size_t dest = 0; dest < graph.get_size(); ++dest) {
    if (!IsAttended(dest)) {
      int pheromone = pheromones_(start, dest);
      int edge_length = graph(start, dest);
      float numerator = CalculateNumerator(pheromone, edge_length);
      probabilities_.push_back(pair(dest, numerator));
      denominator += numerator;
    }
  }
  return denominator;
}

bool TSPAlgorithm::IsNotAllAttended(Graph &graph) {
  return attended_.size() < graph.get_size();
}

bool TSPAlgorithm::IsAttended(const int j) {
  return find(attended_.begin(), attended_.end(), j) != attended_.end();
}

float TSPAlgorithm::CalculateNumerator(const int pheromone,
                                       const int edge_length) {
  return pow(pheromone, kAlpha_) + 1 / pow(edge_length, kBeta_);
}

void TSPAlgorithm::DivideProbabilitiesByDenominator(const float denominator) {
  for (size_t i = 0; i < probabilities_.size(); ++i) {
    probabilities_[i].second = probabilities_[i].second / denominator * 100;
    // std::cout << probabilities[i].second << "\n";
  }
}

float TSPAlgorithm::GetRandomPercentValue() { return rand() % 101; }

size_t TSPAlgorithm::GetNextDestination(const float random_percent) {
  size_t i = 0, size = probabilities_.size() - 1;
  float summ = 0;
  for (; summ < random_percent && i < size; ++i) {
    summ += probabilities_[i].second;
  }
  return probabilities_[i].first;
}

void TSPAlgorithm::RunPheromonesEvaporation() {
  size_t size = pheromones_.get_size();
  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      if (pheromones_(i, j) - kPheromon_evaporation_rate_ < 0) {
        pheromones_(i, j);
      } else {
        pheromones_(i, j) -= kPheromon_evaporation_rate_;
      }
    }
  }
}

void TSPAlgorithm::AddPheromoneTrack(size_t start, size_t dest) {
  pheromones_(start, dest) += kPheromone_track_;
}

void TSPAlgorithm::SetNewResult(TsmResult &result) {
  if (result.distance < result_.distance) {
    std::cout << "NEW\n";
    result_ = result;
  }
}

}  // namespace s21
