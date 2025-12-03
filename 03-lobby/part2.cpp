#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

uint64_t findMax(std::string& batteries) {
  int toRemove = batteries.length()-12;
  std::string res;

  for (size_t i = 0; i < batteries.length(); ++i) {
    while (!res.empty() && res.back() < batteries[i] && toRemove > 0) {
      res.pop_back();
      toRemove--;
    }
    res.push_back(batteries[i]);
  }

  res.resize(12);
  return std::stoll(res);
}

int main(void) {
  // std::ifstream input("./test.txt");
  std::ifstream input("./input.txt");
  std::string batteries;

  uint64_t totalSum = 0;

  while (input >> batteries) {
    totalSum += findMax(batteries);
  }

  std::cout << "Final result: " << totalSum << std::endl;
}
