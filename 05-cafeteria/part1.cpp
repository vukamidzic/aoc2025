#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

typedef std::pair<uint64_t, uint64_t> Range;

Range rangeFromString(std::string s) {
  auto pos = s.find_first_of('-');
  return {std::stoll(s.substr(0, pos)), std::stoll(s.substr(pos + 1))};
}

bool isFresh(std::vector<Range> &ranges, uint64_t ingredient) {
  for (auto r : ranges) {
    if (ingredient >= r.first && ingredient <= r.second) {
      return true;
    }
  }

  return false;
}

int main(void) {
  // std::ifstream input("./test.txt");
  std::ifstream input("./input.txt");
  std::string line;
  std::vector<Range> ranges;
  std::vector<uint64_t> ingredients;

  while (input >> line) {
    if (line.find_first_of('-') != std::string::npos) {
      auto range = rangeFromString(line);
      ranges.push_back(range);
    } else {
      ingredients.push_back(std::stoll(line));
    }
  }

  int result = 0;

  for (auto ingredient : ingredients) {
    if (isFresh(ranges, ingredient))
      result++;
  }

  std::cout << "Final result: " << result << std::endl;
}
