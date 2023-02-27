#include "graph.h"

using s21::Graph;

int main() {
  Graph gg;
  gg.LoadGraphFromFile(
      "/Users/hhullen/PROJECTS/github/SimpleNavigator/src/tests/"
      "graph_example.txt");
  gg.ExportGraphToDot(
      "/Users/hhullen/PROJECTS/github/SimpleNavigator/src/graph/dot.txt");
  return 0;
}