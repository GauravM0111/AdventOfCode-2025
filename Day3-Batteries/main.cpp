#include <fstream>
#include <iostream>
#include <string>

int max_joltage(long long bank) {
  int first{};
  int second = bank % 10;
  bank /= 10;

  while (bank != 0) {
    int digit = bank % 10;
    bank /= 10;

    if (digit >= first) {
      if (first > second) second = first;
      first = digit;
    }
  }

  return first * 10 + second;
}

int main() {
  std::ifstream file ("input.txt");

  if (!file.is_open()) {
    std::cerr << "Failed to open file" << std::endl;
    return 1;
  }

  long total_max_joltage{};
  std::string bank{};
  while (std::getline(file, bank)) {
    if (bank.length() < 2) {
      std::cerr << "bank can't be less than 2" << std::endl;
      return 1;
    }

    int jolt = max_joltage(std::stoll(bank));

    std::cout << bank << "\t->" << jolt << "\n";
    total_max_joltage += jolt;
  }

  std::cout << "\nTOTAL: " << total_max_joltage << std::endl;
}
