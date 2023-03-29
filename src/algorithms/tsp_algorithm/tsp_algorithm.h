#ifndef SRC_ALGORITHMS_TSP_ALGORITHM_TSP_ALGORITHM_H_
#define SRC_ALGORITHMS_TSP_ALGORITHM_TSP_ALGORITHM_H_

#include <algorithm>
#include <cmath>
#include <random>
#include <vector>

#include "../../graph/graph.h"

using std::find;
using std::powf;
using std::rand;
using std::vector;

namespace s21 {

struct TsmResult {
  vector<int> vertices;
  double distance;
};

class TSPAlgorithm {
 public:
  TSPAlgorithm() = delete;
  static TsmResult Solve(Graph &graph);

 private:
  static const float alpha_ = 1, beta_ = 1;
  static vector<int> attended_;
  static Graph pheromones_;
  static TsmResult result_;

  static void RunThroughGraphFromVertex(Graph &graph, size_t i);
  static bool IsAttended(int j);
  static float CalculateNumerator(int pheromone, int edge_length);
  static void CalculateProbabilities(vector<float> &probabilities,
                                     float denominator);
};

}  // namespace s21

#endif  // SRC_ALGORITHMS_TSP_ALGORITHM_TSP_ALGORITHM_H_
