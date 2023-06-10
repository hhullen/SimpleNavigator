#include "utility_cli.h"

namespace s21 {

UtilityCLI::UtilityCLI(int argc, const char *argv[]) {
  Argument path = Argument("graph-path", Argument::Type::Path, "");
  Flag input_file = Flag("file", 'f', "", {path});
  Flag output_file = Flag("output", 'o', "", {path});

  Argument mode_name = Argument("mode-name", Argument::Type::Str, "");
  Flag mode = Flag("mode", 'm', "", {mode_name});

  Argument node = Argument("node", Argument::Type::Int, "");
  Flag start = Flag("start", 's', "", {node});
  Flag end = Flag("end", 'e', "", {node});

  command_line_.AddFlags({input_file, output_file, mode, start, end});
  std::cout << "{";
  for (int i = 0; i < argc; ++i) {
    std::cout << "\"" << argv[i] << "\", ";
  }
  std::cout << "}\n";
  command_line_.Read(argc, argv);
  InitialiseAlgorithms();
}

void UtilityCLI::InitialiseAlgorithms() {
  algorithms_runners_["DFS"] = &UtilityCLI::RunDFS;
  algorithms_runners_["BFS"] = &UtilityCLI::RunBFS;
  algorithms_runners_["SPBV"] = &UtilityCLI::RunSPBV;
  algorithms_runners_["SPBA"] = &UtilityCLI::RunSPBA;
  algorithms_runners_["LST"] = &UtilityCLI::RunLST;
  algorithms_runners_["TSP"] = &UtilityCLI::RunTSP;
}

void UtilityCLI::Exec() {
  InitializeGraph();
  RunAlgorithm();
  WriteOutFile();
}

void UtilityCLI::InitializeGraph() {
  // Str file_path = GetOptionParameterIfExists(
  //     "-f",
  //     "No input graph file specified. For instance: ... -f path/to/file.");
  FlagValues file = command_line_.GetFlagValues("--file");
  Str file_path = file.front();
  graph_.LoadGraphFromFile(file_path);
}

void UtilityCLI::RunAlgorithm() {
  Str mode;
  try {
    FlagValues mode_flag = command_line_.GetFlagValues("--mode");
    mode = mode_flag.front();
    // mode = GetOptionParameterIfExists("-m");
  } catch (...) {
    return;
  }

  if (algorithms_runners_.find(mode) == algorithms_runners_.end()) {
    throw invalid_argument("No algorithm named " + mode + ".");
  }
  (this->*algorithms_runners_[mode])();
}

void UtilityCLI::RunDFS() {
  int start_vertex = GetVertexOption("--start");
  vector<int> route = algorithms_.depthFirstSearch(graph_, start_vertex);
  PrintRoute(route);
}

void UtilityCLI::RunBFS() {
  int start_vertex = GetVertexOption("--start");
  vector<int> route = algorithms_.breadthFirstSearch(graph_, start_vertex);
  PrintRoute(route);
}

void UtilityCLI::RunSPBV() {
  int start_vertex = GetVertexOption("--start");
  int end_vertex = GetVertexOption("--end");
  int distance = algorithms_.getShortestPathBetweenVertices(
      graph_, start_vertex, end_vertex);
  cout << "Distance: " << distance << "\n";
}

void UtilityCLI::RunSPBA() {
  Graph result = algorithms_.getShortestPathsBetweenAllVertices(graph_);
  Graph::Print(result);
}

void UtilityCLI::RunLST() {
  Graph result(algorithms_.getLeastSpanningTree(graph_));
  Graph::Print(result);
}

void UtilityCLI::RunTSP() {
  TsmResult result = algorithms_.solveTravelingSalesmanProblem(graph_);
  PrintRoute(result.vertices);
  cout << "Distance: " << result.distance << "\n";
}

void UtilityCLI::WriteOutFile() {
  Str file_path;
  try {
    FlagValues output = command_line_.GetFlagValues("--output");
    file_path = output.front();
    // file_path = GetOptionParameterIfExists("-o");
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

int UtilityCLI::GetVertexOption(const Str &name) {
  FlagValues flag_vertex = command_line_.GetFlagValues(name);
  Str vertex = flag_vertex.front();
  return atoi(vertex.data());
}

}  // namespace s21
