#ifndef SRC_UTILITY_CLI_UTILITY_CLI_H_
#define SRC_UTILITY_CLI_UTILITY_CLI_H_

#include <iostream>
#include <map>
#include <string>

#include "../algorithms/graph_algorithms.h"
#include "../graph/graph.h"

using s21::Graph;
using s21::GraphAlgorithms;
using std::invalid_argument;
using std::map;
using std::string;

namespace s21 {

class UtilityCLI {
 public:
  UtilityCLI(int argc, char* argv[]);
  void Exec();

 private:
  map<string, void (UtilityCLI::*)()> algorithms_runners_;
  map<string, string> arguments_;

  GraphAlgorithms algorithms_;
  int start_vertex_;
  int end_vertex_;
  Graph graph_;

  void InitialiseAlgorithms();
  void ReadArguments(int argc, char* argv[]);
  bool IsOption(string& arg);
  void CheckNextPresence(int i, int argc, string& arg);

  void InitializeGraph();
  string GetOptionParameterIfExists(string option,
                                    string exception_message = "");
  void RunAlgorithm();
  void DFS();
  void BFS();
  void SPBV();
  void SPBA();
  void LST();
  void TSP();
  void WriteOutFile();
};

}  // namespace s21

#endif  // SRC_UTILITY_CLI_UTILITY_CLI_H_
