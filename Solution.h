#include <vector>
#include <string>

struct Solution {
  std::vector<std::string> input{};
  
  Solution(const char* input_file_name);
  virtual void solve() = 0;
};
