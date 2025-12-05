#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

typedef std::pair<uint64_t, uint64_t> Range;

Range rangeFromString(std::string s) {
  auto pos = s.find_first_of('-');
  return {std::stoll(s.substr(0, pos)), std::stoll(s.substr(pos + 1))};
}

void mergeRanges(std::vector<Range> &ranges) {
  std::sort(ranges.begin(), ranges.end());

  std::vector<Range> merged;
  merged.push_back(ranges[0]);

  for (size_t i = 1; i < ranges.size(); ++i) {
    auto &last = merged.back();
    auto &curr = ranges[i];

    if (curr.first <= last.second)
      last.second = std::max(last.second, curr.second);
    else
      merged.push_back(curr);
  }

  ranges = merged;
}

int main(void) {
  // std::ifstream input("./test.txt");
  std::ifstream input("./input.txt");
  std::vector<Range> ranges;
  std::string line;

  while (std::getline(input, line)) {
    if (line.find_first_of('-') != std::string::npos) {
      auto range = rangeFromString(line);
      ranges.push_back(range);
    }
    else break;
  }

  mergeRanges(ranges);
  uint64_t result = 0;

  for (auto r : ranges) {
    result += (r.second - r.first) + 1;
  }

  std::cout << "Final result: " << result << std::endl;
}
