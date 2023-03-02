#ifndef SRC_GRAPH_GRAPH_H_
#define SRC_GRAPH_GRAPH_H_

#include <dot_writer/DotWriter.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace s21 {

using DotWriter::Edge;
using DotWriter::EdgeAttributeSet;
using DotWriter::Node;
using DotWriter::RootGraph;
using std::atoi;
using std::getline;
using std::ifstream;
using std::invalid_argument;
using std::isdigit;
using std::ofstream;
using std::string;
using std::to_string;
using std::vector;

class AdjacencyMatrix {
 public:
  void Clear() {
    matrix_.clear();
    matrix_.shrink_to_fit();
  }

  void Resize(int size) {
    matrix_.resize(size);
    matrix_.shrink_to_fit();
    for (vector<int> &row : matrix_) {
      row.resize(size);
      row.shrink_to_fit();
    }
  }

  size_t Size() { return matrix_.size(); }
  int &operator()(int i, int j) { return matrix_[i][j]; }

 private:
  vector<vector<int>> matrix_;
};

class Graph {
 public:
  Graph();
  explicit Graph(int size);
  ~Graph();

  int &operator()(int i, int j);

  void Resize(int size);
  size_t get_size();
  void LoadGraphFromFile(const string &path);
  void ExportGraphToDot(const string &path,
                        const string &graph_name = "somegraph");

 private:
  AdjacencyMatrix matrix_;
  ifstream *input_file_;
  ofstream *output_file_;
  vector<Node *> nodes_;

  void IsInputFileOpened();
  void IsOutputFileOpened();
  void ReadAdjacencyMatrixSize();
  void ReadAdjacencyMatrix();
  void ReadLineToMatrixRow(string &line, int row);
  void ShiftToNextNumber(string &line, size_t *i);
  void WriteDotWriterObject(const string &graph_name);
  void AddNodesToDotWriterObject(RootGraph &dot_object);
  void AddEdgesToDotWriterObject(RootGraph &dot_object);
  void AddEdgeBetwenNodesToDotWriterObject(int i, int j, RootGraph &dot_object);
};

}  // namespace s21

#endif  // SRC_GRAPH_GRAPH_H_
