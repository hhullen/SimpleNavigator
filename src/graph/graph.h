#ifndef SRC_GRAPH_GRAPH_H_
#define SRC_GRAPH_GRAPH_H_

#include <dot_writer/DotWriter.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::atoi;
using std::getline;
using std::ifstream;
using std::invalid_argument;
using std::isdigit;
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
  void LoadGraphFromFile(const string &path);
  void ExportGraphToDot(const string &path);

 private:
  vector<vector<int>> adjacency_matrix_;
  ifstream *input_file_;
  ofstream *output_file_;

  void IsInputFileOpened();
  void IsOutputFileOpened();
  void ReadAdjacencyMatrixSize();
  void ReadAdjacencyMatrix();
  void IsLineCorrect(string &line);
  void ReadLineToMatrixRow(string &line, int row);
  void ShiftToNextNumber(string &line, size_t *i);
  void CreateDotWriterObject();

  void PRINT();  // !!!
};

}  // namespace s21

#endif  // SRC_GRAPH_GRAPH_H_
