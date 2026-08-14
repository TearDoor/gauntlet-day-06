#include "Grid.hpp"

#include <iostream>
#include <map>
#include <queue>
#include <string>

struct Node {
  Cell cell;
  int f;
};

struct ByF {
  bool operator()(const Node &a, const Node &b) { return a.f > b.f; }
};

int manhattan(Cell a, Cell b) {
  return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

std::vector<Cell> reconstruct(std::map<Cell, Cell> cameFrom, Cell goal) {
  std::vector<Cell> path;
  Cell c = goal;
  path.push_back(c);
  while (cameFrom.count(c)) {
    c = cameFrom[c];
    path.push_back(c);
  }

  return path;
}

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    std::cerr << "Usage: <map>\n";
    return 1;
  }
  Grid grid = Grid::load(argv[1]);

  std::priority_queue<Node, std::vector<Node>, ByF> open;

  Cell start = grid.start(), goal = grid.goal();
  std::map<Cell, int> g;
  std::map<Cell, Cell> cameFrom;
  g[start] = 0;
  std::vector<Cell> path;

  open.push({start, manhattan(start, goal)});
  while (!open.empty()) {
    Node cur = open.top();
    open.pop();
    if (cur.cell == goal) {
      path = reconstruct(cameFrom, goal);
      grid.printPath(path);
      std::cout << "path length: " << path.size() - 1 << '\n';
      break;
    }
    for (Cell nb : grid.neighbours(cur.cell)) {
      int tentativeG = g[cur.cell] + 1;

      auto it = g.find(nb);
      if (it == g.end() || tentativeG < it->second) {
        g[nb] = tentativeG;
        cameFrom[nb] = cur.cell;

        open.push({nb, tentativeG + manhattan(nb, goal)});
      }
    }
  }
  if (path.empty()) {
    std::cout << "no path\n";
  }
  return 0;
}
