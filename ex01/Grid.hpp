#pragma once

#include <ostream>
#include <string>
#include <vector>

struct Cell {
  int x, y;
};

std::ostream &operator<<(std::ostream &os, const Cell &c);

class Grid {
public:
  static Grid load(const std::string &path);
  bool inBounds(Cell c) const;
  bool isOpen(Cell c) const;
  std::vector<Cell> neighbours(Cell c) const;
  Cell start() const;
  Cell goal() const;
  void printMap() const;

private:
  std::vector<std::string> m_grid;
  int m_width;
  int m_height;
  Cell m_start;
  Cell m_goal;
  char at(const Cell &c) const;
};
