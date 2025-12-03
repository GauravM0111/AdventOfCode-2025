#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::ifstream file ("input.txt");

  if (!file.is_open()) {
    std::cerr << "Failed to open file" << std::endl;
    return 1;
  }
  
  int dial = 50;
  int zeros = 0;
  char direction;

  while (file.get(direction)) {
    std::string distance_str;
    std::getline(file, distance_str);

    int distance = std::stoi(distance_str);

    std::cout << direction << distance << ":\t" << dial << "\t-> ";

    int full_rotations = distance / 100;
    zeros += full_rotations;
    distance = distance % 100;

    int dir_sign = 1;
    if (direction == 'L') {
      dir_sign = -1;
    }

    while (distance-- > 0) {
      dial += dir_sign;

      if (dial == -1) dial = 99;
      else if (dial == 100) dial = 0;

      if (dial == 0) zeros++;
    }

    std::cout << zeros << "\n";
  }

  std::cout << "zero count: " << zeros << std::endl;
}
