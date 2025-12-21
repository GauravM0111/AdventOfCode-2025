#include "../Solution.h"

#include <vector>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <numeric>
#include <functional>

struct HWPart1 : Solution {
  using Solution::Solution;

  std::vector<std::vector<std::int64_t>> build_num_grid() {
    std::vector<std::vector<std::int64_t>> grid(input.size()-1);

    for (std::int64_t r_index = 0; r_index < input.size()-1; r_index++) {
      const auto& line = input.at(r_index);
      auto start_d = std::find_if_not(line.cbegin(), line.cend(), [](char c) { return std::isspace(c); });

      while (start_d != line.cend()) {
        auto end_d = std::find_if(start_d, line.cend(), [](char c) { return std::isspace(c); });

        std::int64_t num = std::stoi(std::string(start_d, end_d));
        grid.at(r_index).push_back(num);

        start_d = std::find_if_not(end_d, line.cend(), [](char c) { return std::isspace(c); });
      }

      for (std::int64_t num : grid.at(r_index)) {
        std::cout << num << " ";
      }
      std::cout << std::endl;
    }

    return grid;
  }

  std::vector<char> get_operators() {
    std::vector<char> ops{};
    std::string op_line = *input.crbegin();

    auto it = std::find_if_not(op_line.cbegin(), op_line.cend(), [](char c) { return std::isspace(c); });
    while (it != op_line.cend()) {
      ops.push_back(*it);
      std::cout << *it << " ";
      it = std::find_if_not(it+1, op_line.cend(), [](char c) { return std::isspace(c); });
    }
    std::cout << std::endl;

    return ops;
  }

  void solve() override {
    std::vector<std::vector<std::int64_t>> grid = build_num_grid();
    std::cout << "---------------" << std::endl;
    std::vector<char> ops = get_operators();

    std::int64_t grand_total{};

    for (size_t c_index = 0; c_index < ops.size(); c_index++) {
      std::function<std::int64_t(std::int64_t, std::int64_t)> op = std::plus<std::int64_t>();
      if (ops.at(c_index) == '*') op = std::multiplies<std::int64_t>();

      size_t r_index = 0;
      std::int64_t res = grid.at(r_index++).at(c_index);

      while (r_index < grid.size()) {
        res = op(res, grid.at(r_index++).at(c_index));
      }

      std::cout << res << " ";
      grand_total += res;
    }
    std::cout << std::endl;

    std::cout << "grand_total: " << grand_total << std::endl;
  }
};

int main() {
  HWPart1("input.txt").solve();
}
