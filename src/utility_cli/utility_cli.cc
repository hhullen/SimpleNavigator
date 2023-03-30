#include "utility_cli.h"

namespace s21 {

UtilityCLI::UtilityCLI(int argc, char* argv[])
    : start_vertex_(1), end_vertex_(1) {
  ReadArguments(argc, argv);
  InitialiseAlgorithms();
}

void UtilityCLI::InitialiseAlgorithms() {
  algorithms_runners_["DFS"] = &UtilityCLI::DFS;
  algorithms_runners_["BFS"] = &UtilityCLI::BFS;
  algorithms_runners_["SPBV"] = &UtilityCLI::SPBV;
  algorithms_runners_["SPBA"] = &UtilityCLI::SPBA;
  algorithms_runners_["LST"] = &UtilityCLI::LST;
  algorithms_runners_["TSP"] = &UtilityCLI::TSP;
}

void UtilityCLI::ReadArguments(int argc, char* argv[]) {
  for (int i = 0; i < argc; ++i) {
    string arg(argv[i]);
    if (IsOption(arg)) {
      CheckNextPresence(i, argc, arg);
      arguments_[arg] = string(argv[i + 1]);
    }
  }
}

bool UtilityCLI::IsOption(string& arg) {
  return arg.size() > 1 && arg[0] == '-';
}

void UtilityCLI::CheckNextPresence(int i, int argc, string& arg) {
  if (!(i + 1 < argc)) {
    throw invalid_argument("No parameter specified to " + arg + " option.");
  }
}

void UtilityCLI::Exec() {
  InitializeGraph();
  RunAlgorithm();
  WriteOutFile();
}

void UtilityCLI::InitializeGraph() {
  string file_path = GetOptionParameterIfExists(
      "-f", "No input graph file specified. For instance: -f path/to/file.");
  graph_.LoadGraphFromFile(file_path);
}

string UtilityCLI::GetOptionParameterIfExists(string option,
                                              string exception_message) {
  if (arguments_.find(option) == arguments_.end()) {
    throw invalid_argument(exception_message);
  }

  return arguments_.find(option)->second;
}

void UtilityCLI::RunAlgorithm() {
  string mode;
  try {
    mode = GetOptionParameterIfExists("-m");
  } catch (...) {
    return;
  }

  if (algorithms_runners_.find(mode) == algorithms_runners_.end()) {
    throw invalid_argument("No algorithm named " + mode + ".");
  }
  (this->*algorithms_runners_[mode])();
}

void UtilityCLI::DFS() { std::cout << "DFS RUN"; }

void UtilityCLI::BFS() {}

void UtilityCLI::SPBV() {}

void UtilityCLI::SPBA() {}

void UtilityCLI::LST() {}

void UtilityCLI::TSP() {
  std::cout << "TSP RUN\n";
  TsmResult result = algorithms_.solveTravelingSalesmanProblem(graph_);
  std::cout << result.distance << "\n";
}

void UtilityCLI::WriteOutFile() {
  string file_path;
  try {
    file_path = GetOptionParameterIfExists("-o");
  } catch (...) {
    return;
  }
  graph_.ExportGraphToDot(file_path);
}

}  // namespace s21
