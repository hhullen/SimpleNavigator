#ifndef SRC_UTILITY_CLI_UTILITY_CLI_H_
#define SRC_UTILITY_CLI_UTILITY_CLI_H_

#include <cmd_args/cmd_args.h>

#include <iostream>
#include <map>
#include <string>

#include "../algorithms/graph_algorithms.h"
#include "../graph/graph.h"

namespace s21 {

using hhullen::Argument;
using hhullen::CMDArgs;
using hhullen::Flag;
using s21::Graph;
using s21::GraphAlgorithms;
using std::atoi;
using std::cout;
using std::invalid_argument;
using std::isdigit;
using std::map;
using Str = std::string;
using FlagValues = std::list<Str>;

class UtilityCLI {
 public:
  UtilityCLI() = delete;
  UtilityCLI(int argc, const char* argv[]);
  void Exec();

 private:
  map<string, void (UtilityCLI::*)()> algorithms_runners_;
  CMDArgs command_line_;

  GraphAlgorithms algorithms_;
  Graph graph_;

  void InitialiseAlgorithms();

  void InitializeGraph();

  void RunAlgorithm();
  void RunDFS();
  void RunBFS();
  void RunSPBV();
  void RunSPBA();
  void RunLST();
  void RunTSP();
  void WriteOutFile();
  void PrintRoute(const vector<int>& vertices);
  int GetVertexOption(const Str& name);
};

}  // namespace s21

#endif  // SRC_UTILITY_CLI_UTILITY_CLI_H_
