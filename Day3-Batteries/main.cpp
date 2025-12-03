#include <fstream>
#include <iostream>
#include <string>
#include <cstdint>
#include <algorithm>


std::int64_t max_joltage(std::string bank) {
  std::int64_t joltage{};
  auto start = bank.begin();
  
  for (int i = 11; i >= 0; i--) {
    auto max_digit_pos = std::max_element(start, bank.end() - i);
    start = max_digit_pos + 1;

    int max_digit = *max_digit_pos - '0';
    joltage += max_digit * std::pow(10, i);
  }

  return joltage;
}

int main() {
  std::ifstream file ("input.txt");

  if (!file.is_open()) {
    std::cerr << "Failed to open file" << std::endl;
    return 1;
  }

  std::int64_t total_max_joltage{};
  std::string bank{};
  while (std::getline(file, bank)) {
    if (bank.length() < 2) {
      std::cerr << "bank can't be less than 2" << std::endl;
      return 1;
    }

    std::int64_t jolt = max_joltage(bank);

    std::cout << bank << "\t->" << jolt << "\n";
    total_max_joltage += jolt;
  }

  std::cout << "\nTOTAL: " << total_max_joltage << std::endl;
}
