#include "utility_cli.h"

namespace s21 {

UtilityCLI::UtilityCLI(int argc, char *argv[]) {
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

void UtilityCLI::ReadArguments(int argc, char *argv[]) {
  for (int i = 0; i < argc; ++i) {
    string arg(argv[i]);
    if (IsOption(arg)) {
      CheckNextPresence(i, argc, arg);
      arguments_[arg] = string(argv[i + 1]);
    }
  }
}

bool UtilityCLI::IsOption(const string &arg) {
  return arg.size() == 2 && arg[0] == '-' && !isdigit(arg[1]);
}

void UtilityCLI::CheckNextPresence(int i, int argc, const string &arg) {
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
      "-f",
      "No input graph file specified. For instance: ... -f path/to/file.");
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

void UtilityCLI::DFS() {
  int start_vertex = GetStartVertexOption();
  vector<int> route = algorithms_.depthFirstSearch(graph_, start_vertex);
  PrintRoute(route);
}

void UtilityCLI::BFS() {
  int start_vertex = GetStartVertexOption();
  vector<int> route = algorithms_.breadthFirstSearch(graph_, start_vertex);
  PrintRoute(route);
}

void UtilityCLI::SPBV() {
  int start_vertex = GetStartVertexOption();
  int end_vertex = GetEndVertexOption();
  int distance = algorithms_.getShortestPathBetweenVertices(
      graph_, start_vertex, end_vertex);
  cout << "Distance: " << distance << "\n";
}

void UtilityCLI::SPBA() {
  Graph result = algorithms_.getShortestPathsBetweenAllVertices(graph_);
  Graph::Print(result);
}

void UtilityCLI::LST() {
  Graph result(algorithms_.getLeastSpanningTree(graph_));
  Graph::Print(result);
}

void UtilityCLI::TSP() {
  TsmResult result = algorithms_.solveTravelingSalesmanProblem(graph_);
  PrintRoute(result.vertices);
  cout << "Distance: " << result.distance << "\n";
}

int UtilityCLI::GetStartVertexOption() {
  string start_vertex_option = GetOptionParameterIfExists(
      "-s", "No start vertex specified. For instance: ... -s 3.");
  return atoi(start_vertex_option.data());
}

int UtilityCLI::GetEndVertexOption() {
  string end_vertex_option = GetOptionParameterIfExists(
      "-e", "No end vertex specified. For instance: ... -e 7.");
  return atoi(end_vertex_option.data());
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

void UtilityCLI::PrintRoute(const vector<int> &vertices) {
  size_t i = 0;
  for (; i < vertices.size() - 1; ++i) {
    cout << vertices[i] << "-";
  }
  cout << vertices[i] << "\n";
}

}  // namespace s21
