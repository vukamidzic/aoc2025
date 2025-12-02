#include <iostream>
#include <fstream>
#include <string>

const int TOTAL = 100;

int main(void) {
  // std::ifstream in("./test.txt");
  std::ifstream in("./input.txt");
  std::string line;

  int currIdx = 50;
  int res = 0;

  while (in >> line) {
    int direction = (line[0] == 'L')? -1 : 1;
    int numRot = std::stoi(line.substr(1));

    res += std::abs(numRot / TOTAL);
    numRot %= TOTAL;
    if (numRot < 0) {
      numRot += TOTAL;
    }

    int newIdx = currIdx + direction*numRot;

    if (currIdx != 0) {
      if (newIdx >= TOTAL || newIdx <= 0) res++;
    }
    
    currIdx = (newIdx + TOTAL) % TOTAL;
    std::cout << "Current: " << currIdx << std::endl;
  }

  std::cout << "Final result: " << res << std::endl;
}
