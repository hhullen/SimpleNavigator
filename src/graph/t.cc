#include "graph.h"

using s21::Graph;

int main() {
  Graph gg;
  gg.LoadGraphFromFile(
      "/Users/hhullen/PROJECTS/github/SimpleNavigator/src/tests/"
      "graph_example.txt");
  return 0;
}