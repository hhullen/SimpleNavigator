#include "graph.h"

namespace s21 {
Graph::Graph() {}

Graph::Graph(int size) { Resize(size); }

Graph::~Graph() {
  adjacency_matrix_.clear();
  adjacency_matrix_.shrink_to_fit();
}

int &Graph::operator()(int i, int j) { return adjacency_matrix_[i][j]; }

void Graph::Resize(int size) {
  adjacency_matrix_.resize(size);
  adjacency_matrix_.shrink_to_fit();
  for (vector<int> &row : adjacency_matrix_) {
    row.resize(size);
    row.shrink_to_fit();
  }
}

int Graph::get_size() { return adjacency_matrix_.size(); }

void Graph::LoadGraphFromFile(const string &path) {
  ifstream file(path);
  input_file_ = &file;

  IsInputFileOpened();
  ReadAdjacencyMatrixSize();
  ReadAdjacencyMatrix();

  input_file_->close();
  input_file_ = nullptr;
  PRINT();
}

void Graph::IsInputFileOpened() {
  if (!input_file_->is_open()) {
    throw invalid_argument("File cuold not be opened.");
  }
}

void Graph::ReadAdjacencyMatrixSize() {
  string line;
  getline(*input_file_, line, '\n');
  int size = atoi(line.data());
  if (size < 1) {
    input_file_->close();
    throw invalid_argument("Incorrect matrix size");
  }
  Resize(size);
}

void Graph::ReadAdjacencyMatrix() {
  string line;
  int row = 0;
  while (getline(*input_file_, line, '\n') && row < get_size()) {
    IsLineCorrect(line);
    ReadLineToMatrixRow(line, row);
    ++row;
  }
}

void Graph::IsLineCorrect(string &line) {
  if (line.size() * 2 < get_size()) {
    input_file_->close();
    throw invalid_argument("Incorrect matrix row");
  }
}

void Graph::ReadLineToMatrixRow(string &line, int row) {
  int col = 0;
  for (size_t i = 0; i < line.size(); ++i) {
    char *number = &(line.data())[i];
    adjacency_matrix_[row][col] = atoi(number);
    ++col;
    ShiftToNextNumber(line, &i);
  }
}

void Graph::ShiftToNextNumber(string &line, size_t *i) {
  while (isdigit(line.data()[*i]) && *i < line.size()) {
    ++(*i);
    char *number = &(line.data())[*i];
  }
  while (!isdigit(line.data()[*i]) && *i < line.size()) {
    ++(*i);
    char *number = &(line.data())[*i];
  }
  --(*i);
}

void Graph::ExportGraphToDot(const string &path) {
  ofstream file(path);
  output_file_ = &file;

  IsOutputFileOpened();
  CreateDotWriterObject();

  output_file_->close();
  output_file_ = nullptr;
}

void Graph::IsOutputFileOpened() {
  if (!output_file_->is_open()) {
    throw invalid_argument("File cuold not be opened.");
  }
}

void Graph::CreateDotWriterObject() {
  // DotWriter::Node node("a");
  // DotWriter::Graph dot_object;
}

void Graph::PRINT() {
  for (int i = 0; i < get_size(); ++i) {
    for (int j = 0; j < get_size(); ++j) {
      std::cout << adjacency_matrix_[i][j] << " ";
    }
    std::cout << "\n";
  }
}

}  // namespace s21
