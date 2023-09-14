#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "include/gol.h"

class Window {
private:
  int width_, height_;
  int rows_, cols_; 
  sf::RenderWindow window_;
  GOL alive_matrix_;
  int cell_len_;
  std::array<int, 2> remap_point(int mouse_x, int mouse_y);
  void draw_map();
  void draw_grid();
  void fill_cells();

public:
  Window(int width, int height, std::string name="Game of life", int rows=50, int cols=50);
  int run();
  
};
