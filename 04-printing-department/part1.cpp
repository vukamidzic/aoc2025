#include <fstream>
#include <iostream>
#include <vector>

bool insideLimits(std::pair<int, int> pos, int rowMax, int colMax) {
  return (pos.first >= 0 && pos.first < rowMax && pos.second >= 0 &&
          pos.second < colMax);
}

int findAccessible(std::vector<std::vector<int>> &mat) {
  int n = mat.size();
  int m = mat[0].size();

  std::vector<std::pair<int, int>> neighs = {
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {0, -1},
    {0, 1},
    {1, -1},
    {1, 0},
    {1, 1}
  };

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (mat[i][j] >= 0) {
        for (auto neigh : neighs) {
          auto ni = i+neigh.first;
          auto nj = j+neigh.second;
          if (insideLimits({ni,nj}, n, m) && mat[ni][nj] != -1)
            mat[i][j]++; 
        }
      } 
    }
  }
  
  int cnt = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (mat[i][j] != -1 && mat[i][j] < 4) cnt++;
    }
  }

  return cnt;
}

int main(void) {
  // std::ifstream input("./test.txt");
  std::ifstream input("./input.txt");
  std::vector<std::vector<int>> mat;
  std::string line;

  while (input >> line) {
    std::vector<int> row;
    for (auto c : line) {
      row.push_back((c == '@') ? 0 : -1);
    }
    mat.push_back(row);
  }

  int result = findAccessible(mat);
  std::cout << "Final result: " << result << std::endl;
}
