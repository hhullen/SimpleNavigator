#ifndef SRC_ALGORITHMS_TSP_ALGORITHM_TSP_ALGORITHM_H_
#define SRC_ALGORITHMS_TSP_ALGORITHM_TSP_ALGORITHM_H_

#include <algorithm>
#include <random>
#include <vector>

#include "../../graph/graph.h"

namespace s21 {

using std::find;
using std::pair;
using std::pow;
using std::rand;
using std::vector;

struct TsmResult {
  TsmResult() : distance(0) {}
  vector<int> vertices;
  double distance;
};

class TSPAlgorithm {
 public:
  TsmResult Solve(Graph &graph);

 private:
  vector<pair<size_t, float>> probabilities_;
  const int kPheromone_track_ = 5, kPheromon_evaporation_rate_ = 1;
  const float kAlpha_ = 1, kBeta_ = 1;
  vector<int> attended_;
  Graph pheromones_;
  TsmResult result_;

  void CloseRoute(Graph &graph);
  void RunThroughGraphFromVertex(Graph &graph, size_t i);
  float GetProbabilitiesDenominator(Graph &graph, size_t start);
  bool IsNotAllAttended(Graph &graph);
  bool IsAttended(const int j);
  float CalculateNumerator(const int pheromone, const int edge_length);
  void DivideProbabilitiesByDenominator(const float denominator);
  float GetRandomPercentValue();
  size_t GetNextDestination(const float random_percent);
  void RunPheromonesEvaporation();
  void AddPheromoneTrack(size_t start, size_t dest);
  void UpdateResult(TsmResult &result, int distance, size_t dest);
  void SetNewResult(const TsmResult &result);
};

}  // namespace s21

#endif  // SRC_ALGORITHMS_TSP_ALGORITHM_TSP_ALGORITHM_H_
