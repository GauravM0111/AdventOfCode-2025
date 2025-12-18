#include "../Solution.h"

#include <map>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstdint>

struct FreshIngredientsPart1 : Solution {
  using Solution::Solution;
  std::map<std::int64_t, std::int64_t> fresh_id_ranges{};

  void print_fresh_id_ranges() {
    for (const auto& range : fresh_id_ranges) {
      std::cout << range.first << " - " << range.second << "\n";
    }
    std::cout << std::endl;
  }

  void insert_fresh_id_range(std::int64_t start, std::int64_t end) {
    try {
      std::int64_t end_c = fresh_id_ranges.at(start);
      if (end_c >= end) return;
    } catch (std::out_of_range) {}

    fresh_id_ranges[start] = end;

    auto it = fresh_id_ranges.upper_bound(start);
    if (it == fresh_id_ranges.cend()) return;

    // remove all following ranges that are completely within the newly added range
    while (end >= it->second) {
      auto next_it = std::next(it);
      fresh_id_ranges.erase(it);
      it = next_it;
    }

    // merge in case of overlap or back-to-back
    if (end >= it->first-1) {
      end = it->second;
      fresh_id_ranges[start] = end;
      fresh_id_ranges.erase(it);
    }

    it = fresh_id_ranges.lower_bound(start);
    if (it == fresh_id_ranges.cbegin()) return;
    auto prev_it = std::prev(it);

    // merge backward in case of overlap or back-to-back
    if (prev_it->second >= start-1) {
      if (end > prev_it->second) prev_it->second = end;
      fresh_id_ranges.erase(it);
      start = prev_it->first;
    }
  }

  bool is_fresh(std::int64_t id) {
    return std::any_of(
      fresh_id_ranges.cbegin(),
      fresh_id_ranges.cend(),
      [id](const auto& range) {
        return (id >= range.first) && (id <= range.second);
      }
    );
  }

  void solve() override {
    for (int i = 0; i < input.size(); i++) {
      const auto& id_range = input[i];

      if (id_range.empty()) {
        // Part 1
        int num_fresh = std::count_if(
          input.cbegin() + i + 1,
          input.cend(),
          [this](const auto& id) {
            return is_fresh(std::stoll(id));
          }
        );

        std::cout << "num_fresh: " << num_fresh << std::endl;

        // Part 2
        std::int64_t total_fresh{};
        for (const auto& id_range : fresh_id_ranges) {
          total_fresh += (id_range.second - id_range.first) + 1;
        }

        std::cout << "total_fresh: " << total_fresh << std::endl;

        return;
      }

      auto dash_pos = id_range.find('-');
      std::int64_t start = std::stoll(id_range.substr(0, dash_pos));
      std::int64_t end = std::stoll(id_range.substr(dash_pos + 1));

      std::cout << start << " - " << end << "\n";
      std::cout << "-----------------------" << std::endl;

      insert_fresh_id_range(start, end);

      print_fresh_id_ranges();
    }
  }
};

int main() {
  FreshIngredientsPart1("input.txt").solve();
}
