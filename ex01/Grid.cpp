#include "Grid.hpp"

#include <fstream>
#include <iostream>

std::ostream &operator<<(std::ostream &os, const Cell &c) {
  os << '(' << c.x << ',' << c.y << ')';
  return os;
}

Grid Grid::load(const std::string &path) {
  std::string buffer;
  std::ifstream is(path);
  if (!is) {
    std::cerr << "Error: not a valid file\n";
  }

  Grid g;

  int y = 0;
  while (std::getline(is, buffer)) {
    g.m_grid.push_back(buffer);
    for (int x = 0; x < static_cast<int>(buffer.size()); x++) {
      if (buffer[x] == 'S')
        g.m_start = {x, y};
      else if (buffer[x] == 'G')
        g.m_goal = {x, y};
    }
    y++;
  }
  g.m_width = g.m_grid[0].length();
  g.m_height = y;
  // std::cout << "width: " << g.m_width << " height: " << g.m_height << '\n';
  return g;
}

bool Grid::inBounds(Cell c) const {
  return (c.x >= 0 && c.x < m_width && c.y >= 0 && c.y < m_height);
}

bool Grid::isOpen(Cell c) const { return inBounds(c) && (at(c) != '#'); }

Cell Grid::start() const { return m_start; }

Cell Grid::goal() const { return m_goal; }

void Grid::printMap() const {
  for (auto row : m_grid) {
    std::cout << row << '\n';
  }
}

std::vector<Cell> Grid::neighbours(Cell c) const {
  std::vector<Cell> out;
  const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};

  for (int i = 0; i < 4; ++i) {
    Cell n{c.x + dx[i], c.y + dy[i]};
    if (isOpen(n)) {
      out.push_back(n);
    }
  }

  return out;
}

char Grid::at(const Cell &c) const { return m_grid[c.y][c.x]; }
