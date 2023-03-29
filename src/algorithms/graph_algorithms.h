#ifndef SRC_ALGORITHMS_GRAPH_ALGORITHMS_H_
#define SRC_ALGORITHMS_GRAPH_ALGORITHMS_H_
#include "../graph/graph.h"
#include "../include/containers/queue.h"
#include "../include/containers/stack.h"
#include <climits>
namespace s21 {

class GraphAlgorithms {
public:
  GraphAlgorithms();
  vector<int> depthFirstSearch(Graph &graph, int startVertex);
  vector<int> breadthFirstSearch(Graph &graph, int startVertex);
  int getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
  Graph getShortestPathsBetweenAllVertices(Graph &graph);

private:
  //   Graph graph_;
};

} // namespace s21

#endif // SRC_ALGORITHMS_GRAPH_ALGORITHMS_H_
