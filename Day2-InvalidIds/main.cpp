#include <fstream>
#include <iostream>
#include <string>


bool is_invalid(long ID) {
  std::string id = std::to_string(ID);

  if (id.length() == 1) return false;

  std::string repeat_seq = id.substr(0, 1);
  int i = 1;

  while (i < id.length()) {
    if (repeat_seq == id.substr(i, repeat_seq.length())) {
      i += repeat_seq.length();
      continue;
    }

    repeat_seq = id.substr(0, ++i);
    if (repeat_seq.length() > id.length() / 2) return false;
  }

  return true;
}

int main() {
  std::ifstream file ("input.txt");

  if (!file.is_open()) {
    std::cerr << "Failed to open file" << std::endl;
    return 1;
  }

  std::string id_range{};
  long invalid_sum{};
  while (std::getline(file, id_range, ',')) {
    int dash_pos = id_range.find('-');

    long start = std::stol(id_range.substr(0, dash_pos));
    long end = std::stol(id_range.substr(dash_pos+1));

    std::cout << start << " - " << end << "\n" << "INVALID: ";

    for (long id = start; id <= end; id++) {
      if (is_invalid(id)) {
        std::cout << id << ", ";
        invalid_sum += id;
      }
    }
    std::cout << "\n\n";
  }

  std::cout << "\nSUM: " << invalid_sum << "\n";
}
