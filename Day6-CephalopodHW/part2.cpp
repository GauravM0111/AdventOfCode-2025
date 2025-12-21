#include "../Solution.h"

#include <vector>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <numeric>
#include <functional>

struct HWPart2 : Solution {
  using Solution::Solution;

  std::vector<std::vector<int>> build_num_grid() {
    std::vector<std::vector<int>> grid{};
    std::vector<int> problem{};

    for (ssize_t c_index = input.at(0).size()-1; c_index >= 0; c_index--) {
      int num{};
      bool empty_column{true};
  
      for (size_t r_index = 0; r_index < input.size()-1; r_index++) {
        char digit = input.at(r_index).at(c_index);
        if (digit != ' ') {
          empty_column = false;
          num = (num*10) + (digit - '0');
        }
      }

      if (empty_column) {
        grid.push_back(problem);
        problem.clear();
        continue;
      }

      problem.push_back(num);
    }

    grid.push_back(problem);  // last problem has no empty column after it
    return grid;
  }

  std::vector<char> get_operators() {
    std::vector<char> ops{};
    std::string op_line = *input.crbegin();

    auto it = std::find_if_not(op_line.crbegin(), op_line.crend(), [](char c) { return std::isspace(c); });
    while (it != op_line.crend()) {
      ops.push_back(*it);
      it = std::find_if_not(it+1, op_line.crend(), [](char c) { return std::isspace(c); });
    }

    return ops;
  }

  void solve() override {
    std::vector<std::vector<int>> problems = build_num_grid();
    std::vector<char> ops = get_operators();
    std::int64_t grand_total{};

    for (size_t p_index{}; p_index < ops.size(); p_index++) {
      auto problem = &problems.at(p_index);
      std::function<std::int64_t(std::int64_t, std::int64_t)> op = std::plus<std::int64_t>();
      std::int64_t start_val{};
      
      if (ops.at(p_index) == '*') {
        op = std::multiplies<std::int64_t>();
        start_val = 1;
      }

      for (int num : *problem) std::cout << num << " ";
      std::cout << ops.at(p_index) << ": ";

      std::int64_t res = std::accumulate(problem->cbegin(), problem->cend(), start_val, op);
      grand_total += res;
      
      std::cout << res << "\n";
    }

    std::cout << "grand_total: " << grand_total << std::endl;
  }
};

int main() {
  HWPart2("input.txt").solve();
}
