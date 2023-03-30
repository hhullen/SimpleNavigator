#ifndef SRC_ALGORITHMS_GRAPH_ALGORITHMS_H_
#define SRC_ALGORITHMS_GRAPH_ALGORITHMS_H_

#include <containers/queue.h>
#include <containers/stack.h>

#include <climits>

#include "../graph/graph.h"
#include "tsp_algorithm/tsp_algorithm.h"

namespace s21 {

class GraphAlgorithms {
 public:
  GraphAlgorithms();
  vector<int> depthFirstSearch(Graph &graph, int startVertex);
  vector<int> breadthFirstSearch(Graph &graph, int startVertex);
  int getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
  Graph getShortestPathsBetweenAllVertices(Graph &graph);
  TsmResult solveTravelingSalesmanProblem(Graph &graph);
  void ValidateIndexes(Graph &graph, const int *vertex1,
                       const int *vertex2 = nullptr);
};

}  // namespace s21

#endif  // SRC_ALGORITHMS_GRAPH_ALGORITHMS_H_
