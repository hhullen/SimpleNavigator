#ifndef SRC_UTILITY_CLI_UTILITY_CLI_H_
#define SRC_UTILITY_CLI_UTILITY_CLI_H_

#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

#include "../algorithms/graph_algorithms.h"
#include "../graph/graph.h"

using s21::Graph;
using s21::GraphAlgorithms;
using std::invalid_argument;
using std::map;
using std::queue;
using std::string;
using std::vector;

namespace s21 {

class UtilityCLI {
 public:
  UtilityCLI(int argc, char* argv[]);
  void Exec();

 private:
  map<string, string> arguments_;

  Graph graph_;
  int start_vertex_;
  int end_vertex_;

  void ReadArguments(int argc, char* argv[]);
  bool IsOption(string& arg);
  void CheckNextPresence(int i, int argc, string& arg);

  void InitializeGraph();
  string GetOptionParameterIfExists(string option,
                                    string exception_message = "");
  void RunAlgorithm();
  void WriteOutFile();
};

}  // namespace s21

#endif  // SRC_UTILITY_CLI_UTILITY_CLI_H_
