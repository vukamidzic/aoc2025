#include <fstream>
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
    char direction = line[0];
    int numRot = std::stoi(line.substr(1));
    if (direction == 'L') numRot *= -1;

    currIdx = (currIdx + numRot + TOTAL) % TOTAL;
    if (currIdx == 0) res++;

    std::cout << "Current: " << currIdx << std::endl;
  }

  std::cout << "Final result: " << res << std::endl;
}
