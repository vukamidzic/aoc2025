#include <fstream>
#include <iostream>
#include <vector>

static std::vector<std::pair<int, int>> neighs = {
  {-1, -1},
  {-1, 0},
  {-1, 1},
  {0, -1},
  {0, 1},
  {1, -1},
  {1, 0},
  {1, 1}
};

bool insideLimits(std::pair<int, int> pos, int rowMax, int colMax) {
  return (pos.first >= 0 && pos.first < rowMax && pos.second >= 0 &&
          pos.second < colMax);
}

void initState(std::vector<std::vector<int>> &mat) {
  int n = mat.size();
  int m = mat[0].size();

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (mat[i][j] >= 0) {
        for (auto [di, dj] : neighs) {
          std::pair<int, int> neigh = {i + di, j + dj};
          if (insideLimits(neigh, n, m) && mat[neigh.first][neigh.second] != -1)
            mat[i][j]++;
        }
      }
    }
  }
}

int findRemovable(std::vector<std::vector<int>> &mat) {
  int n = mat.size();
  int m = mat[0].size();

  int cnt = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (mat[i][j] != -1 && mat[i][j] < 4)
        cnt++;
    }
  }

  return cnt;
}

void updateState(std::vector<std::vector<int>> &mat) {
  int n = mat.size();
  int m = mat[0].size();

  std::vector<std::pair<int, int>> toRemove;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (mat[i][j] != -1 && mat[i][j] < 4) {
        toRemove.push_back({i, j});
      }
    }
  }

  for (auto [i, j] : toRemove) {
    mat[i][j] = -1;
    for (auto [di, dj] : neighs) {
      std::pair<int, int> neigh = {i + di, j + dj};
      if (insideLimits(neigh, n, m) && mat[neigh.first][neigh.second] != -1)
        mat[neigh.first][neigh.second]--;
    }
  }
}

int findTotalRemovable(std::vector<std::vector<int>> &mat) {
  int total = 0;
  int curr = 0;

  while ((curr = findRemovable(mat)) > 0) {
    total += curr;
    updateState(mat);
  }

  return total;
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

  initState(mat);

  int result = findTotalRemovable(mat);
  std::cout << "Final result: " << result << std::endl;
}
