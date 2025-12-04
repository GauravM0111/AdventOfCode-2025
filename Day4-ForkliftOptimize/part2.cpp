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

int remove_accessible(int row_index, std::vector<std::string>& grid) {
  int accessible{};
  std::string* curr_row = &grid.at(row_index);

  for (int i_roll = 0; i_roll < curr_row->size(); i_roll++) {
    if (curr_row->at(i_roll) != '@') continue;
    int adj_count{};

    for (const auto& offset : ADJACENT) {
      try {
        std::string* adj_row = &grid.at(row_index + offset.first);
        char adj_roll = adj_row->at(i_roll + offset.second);
        if (adj_roll == '@') adj_count++;
      } catch (std::out_of_range) {
        continue;
      }
    }

    if (adj_count < 4) {
        accessible++;
        curr_row->at(i_roll) = '.';
    }
  }

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
  while (std::getline(file, row)) grid.push_back(row);

  int total_accessible{};
  int accessible{};
  do {
    //debug
    for (const auto& row : grid) {
        std::cout << row << "\n";
    }
    std::cout << "\n";

    accessible = 0;
    for (int r_index = 0; r_index < grid.size(); r_index++) {
        accessible += remove_accessible(r_index, grid);
    }
    total_accessible += accessible;
  } while (accessible > 0);

  std::cout << "\nACCESSIBLE: " << total_accessible << std::endl;
}
