#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

int findMax(std::string& batteries) {
  size_t n = batteries.length();
  int currMax = 0;
  
  for (size_t i = 0; i < n-1; ++i) {
    auto it = std::max_element(batteries.begin()+i+1, batteries.end());
    auto comb = std::string() + batteries[i] + (*it);
    currMax = std::max(std::stoi(comb), currMax);
  }

  return currMax;
}

int main(void) {
  // std::ifstream input("./test.txt");
  std::ifstream input("./input.txt");
  std::string batteries;

  int totalSum = 0;

  while (input >> batteries) {
    totalSum += findMax(batteries);
  }

  std::cout << "Final result: " << totalSum << std::endl;
}
