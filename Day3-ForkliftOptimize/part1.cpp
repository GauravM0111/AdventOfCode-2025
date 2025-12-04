#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <array>

constexpr std::array<std::pair<int, int>, 8> ADJACENT{{
  {-1,  -1},    {-1,  0},   {-1,  1},
  {0,   -1},                {0,   1},
  {1,   -1},    {1,   0},   {1,   1}
}};

int get_accessible_count(int row_index, const std::vector<std::string>& grid) {
  int accessible{};
  const std::string* curr_row = &grid.at(row_index);

  for (int i_roll = 0; i_roll < curr_row->size(); i_roll++) {
    if (curr_row->at(i_roll) != '@') {
      std::cout << '.';
      continue;
    }
    int adj_count{};

    for (const auto& offset : ADJACENT) {
      try {
        const std::string* adj_row = &grid.at(row_index + offset.first);
        char adj_roll = adj_row->at(i_roll + offset.second);
        if (adj_roll == '@') adj_count++;
      } catch (std::out_of_range) {
        continue;
      }
    }

    std::cout << adj_count;
    if (adj_count < 4) accessible++;
  }

  std::cout << "\n";
  return accessible;
}

int main() {
  std::ifstream file ("input.txt");

  if (!file.is_open()) {
    std::cerr << "Failed to open file" << std::endl;
    return 1;
  }

  std::vector<std::string> grid{};
  std::string row{};

  for (int i = 0; i < 2; i++) {
    std::getline(file, row);
    grid.push_back(row);
  }

  int accessible{};
  accessible += get_accessible_count(0, grid);  // first row

  while (std::getline(file, row)) {
    grid.push_back(row);
    accessible += get_accessible_count(1, grid);
    grid.erase(grid.begin()); // only 3 rows or less are required for calculation
  }

  accessible += get_accessible_count(1, grid);  // last row
  std::cout << "\nACCESSIBLE: " << accessible << std::endl;
}
