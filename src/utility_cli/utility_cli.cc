#include "utility_cli.h"

namespace s21 {

UtilityCLI::UtilityCLI(int argc, char* argv[]) {
  queue<string> args;
  for (int i = 0; i < argc; ++i) {
    args.push(string(argv[i]));
  }
  InitializeFeatures();
}

void UtilityCLI::InitializeFeatures() {}

void UtilityCLI::Exec() {}

}  // namespace s21
