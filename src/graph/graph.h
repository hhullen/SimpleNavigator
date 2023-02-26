#ifndef SRC_GRAPH_GRAPH_H_
#define SRC_GRAPH_GRAPH_H_

#include <fstream>
#include <string>
#include <vector>

using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

namespace s21 {

class Graph {
 public:
  Graph();
  explicit Graph(int size);
  ~Graph();

  int &operator()(int i, int j);

  void Resize(int size);
  int get_size();
  void LoadGraphFromFile(string &path);
  void ExportGraphToDot(string &path);

 private:
  vector<vector<int>> adjacency_matrix_;
};

}  // namespace s21

#endif  // SRC_GRAPH_GRAPH_H_
