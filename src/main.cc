#include <iostream>

#include "utility_cli/utility_cli.h"

using s21::UtilityCLI;
using std::cerr;
using std::cout;
using std::invalid_argument;

int main(int argc, char* argv[]) {
  int exit_code = 1;
  try {
    UtilityCLI utility(argc, argv);
    utility.Exec();
    exit_code = 0;
  } catch (string message) {
    cout << message << "\n";
  } catch (invalid_argument ex) {
    cerr << "Exception cought: " << ex.what() << "\n";
  } catch (...) {
    cerr << "Unknown execution error\n";
  }
  return exit_code;
}
