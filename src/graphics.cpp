#include "include/graphics.h"

#include <iostream>

Window::Window(int width, int height, std::string name, int rows, int cols) {
  width_ = width;
  height_ = height;
  window_.create(sf::VideoMode(width_, height_), name);
  rows_ = rows;
  cols_ = cols;
  cell_len_ = height_ / rows_;
  alive_matrix_ = GOL(cols_, rows_);
}

int Window::run() {
  bool run_evolution = false;
  while (window_.isOpen())
    {
      sf::Event event;
      while (window_.pollEvent(event))
      {
        switch (event.type)
        {
          case sf::Event::Closed:
            window_.close();
            break;

          case sf::Event::MouseButtonReleased:
            std::array<int, 2> remaped;
            remaped = remap_point(event.mouseButton.x, event.mouseButton.y);
            alive_matrix_.flip_cell(remaped[0], remaped[1]);
            
            break;

          case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Space) {
              run_evolution = !run_evolution;
            }

            break;

          default:
            break;
        }
      }

      window_.clear(sf::Color::Black);
      if (run_evolution) {
        alive_matrix_.update_map();
        sf::sleep(sf::seconds(0.5));

      }
      draw_map();
      window_.display();
    }

  return 0;
}

std::array<int, 2> Window::remap_point(int mouse_x, int mouse_y) {
  int row_id = mouse_y / cell_len_;
  int col_id = mouse_x / cell_len_;
  std::array<int, 2> remaped = {row_id, col_id};
  return remaped;
}

void Window::draw_map() {
  fill_cells();
  draw_grid();
}

void Window::draw_grid() {
  // drawing vertical separating lines
  for (int j = 0; j <= cols_; j++) {
    float x_point = cell_len_ * j + 1;
    sf::Vertex vertical_line[] =
    {
        sf::Vertex(sf::Vector2f(x_point, static_cast<float>(0))),
        sf::Vertex(sf::Vector2f(x_point, static_cast<float>(height_)))
    };
    window_.draw(vertical_line, 2, sf::Lines);
  }

  // drawing horizontal separating lines
  for (int i = 0; i <= cols_; i++) {
    float y_point = cell_len_ * i;
    if (i == cols_) y_point--;  // fixup of line hidden behind window frame
    float right_border = cell_len_ * cols_;
    sf::Vertex horizontal_line[] =
    {
        sf::Vertex(sf::Vector2f(static_cast<float>(0), y_point)),
        sf::Vertex(sf::Vector2f(static_cast<float>(right_border), y_point))
    };
    window_.draw(horizontal_line, 2, sf::Lines);
  }
}

void Window::fill_cells() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++){
      float rect_size = static_cast<float>(cell_len_);
      sf::RectangleShape rectangle(sf::Vector2f(rect_size-1, rect_size-1));
      rectangle.setPosition(j * cell_len_ + 1, i * cell_len_ + 1);
      if (alive_matrix_.get_cell_state(i, j)) {
        rectangle.setFillColor(sf::Color::White);
      } else {
        rectangle.setFillColor(sf::Color::Black);
      }
      window_.draw(rectangle);
    }
  }
}
