#include "Solution.h"

#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>


Solution::Solution(const char* input_file_name) {
  std::ifstream file (input_file_name);

  if (!file.is_open()) {
    throw std::invalid_argument("File not found!");
  }

  std::string line{};
  while (std::getline(file, line)) {
    input.push_back(line);
  }
}
