#include "Grid.hpp"

#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  if (argc <= 3 || (argc - 2) % 2 != 0) {
    std::cerr
        << "Usage: <map> <x> <y> [<x> <y> ...] (x and y must come in pairs)";
    return 1;
  }
  Grid grid = Grid::load(argv[1]);

  grid.printMap();
  std::cout << "start S = " << grid.start() << '\n';
  std::cout << "goal  G = " << grid.goal() << '\n';

  for (int i = 2; i < argc; i += 2) {
    Cell cell{std::stoi(argv[i]), std::stoi(argv[i + 1])};
    std::vector<Cell> neighbours = grid.neighbours(cell);
    std::cout << "neighbours" << cell << ": ";
    for (const auto &c : neighbours) {
      std::cout << c << ' ';
    }
    std::cout << '\n';
  }

  return 0;
}
