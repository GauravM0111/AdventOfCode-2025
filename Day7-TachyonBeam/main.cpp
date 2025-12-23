#include "../Solution.h"
#include <iostream>
#include <stdexcept>
#include <unordered_map>

struct Tachyon : Solution {
  std::unordered_map<size_t, std::int64_t> beams{};

  Tachyon(const char* input_file_name) : Solution(input_file_name) {
    size_t S_pos = input.at(0).find('S');

    if (S_pos == std::string::npos) {
      throw std::invalid_argument("Character 'S' not found in first line");
    }

    beams.emplace(S_pos, 1);
  }

  void addBeams(size_t beam_pos, std::int64_t num, std::unordered_map<size_t, std::int64_t>& beams) {
    auto [it, inserted] = beams.emplace(beam_pos, num);
    if (inserted) return;

    it->second += num;
  }

  void removeBeam(size_t beam_pos, std::unordered_map<size_t, std::int64_t>& beams) {
    beams.erase(beam_pos);
  }

  void solve() override {
    std::cout << *input.cbegin() << std::endl;
        
    for (auto layer = input.cbegin()+1; layer != input.cend(); layer++) {
      auto split_beams(beams);

      for (auto& [beam_pos, beam_count] : beams) {
        if (layer->at(beam_pos) != '^')         continue;

        removeBeam(beam_pos, split_beams);
        
        if (beam_pos-1 >= 0) {
          addBeams(beam_pos-1, beam_count, split_beams);
        }
        if (beam_pos+1 < input.at(0).size()) {
          addBeams(beam_pos+1, beam_count, split_beams);
        }
      }

      beams = std::move(split_beams);

      for (size_t c_index{}; c_index < layer->size(); c_index++) {
        auto beam = beams.find(c_index);

        if (beam == beams.cend()) {
          std::cout << " " << layer->at(c_index);
          continue;
        }

        std::cout << " " << beam->second;
      }
      std::cout << std::endl;
    }

    std::int64_t timelines{};
    for (auto& [beam, count] : beams) timelines += count;

    std::cout << "timelines: " << timelines;
  }
};

int main() {
  Tachyon("input.txt").solve();
}
