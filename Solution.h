#include "Logger.h"

#include <vector>
#include <string>

struct Solution {
  std::vector<std::string> input{};
  Logger logger{};
    
  Solution() = delete;
  Solution(const char* input_file_name);
  virtual void solve() = 0;
};

// // Boilerplate example
// #include "../Solution.h"

// struct Problem : Solution {
//   using Solution::Solution;

//   void solve() override {
//     return;
//   }
// };

// int main() {
//   Problem("test.txt").solve();
// }
