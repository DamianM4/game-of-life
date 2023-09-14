#include "include/gol.h"

#include <iostream>

GOL::GOL(int width, int height) {
	width_ = width;
	height_ = height;
	create_map(width, height);
}

GOL& GOL::operator=(GOL &&new_GOL) {
	width_ = std::move(new_GOL.width_);
	height_ = std::move(new_GOL.height_);
	create_map(width_, height_);
	return *this;
}

void GOL::create_map(int width, int height) {
	current_map_.resize(height);
	new_map_.resize(height);

	for (auto &row: current_map_) {
		row.resize(width);
	}

	for (auto &row: new_map_) {
		row.resize(width);
	}
}

void GOL::change_cell(int x, int y, bool active) {
	if (x < current_map_.size()) {
		if (y < current_map_[0].size()) {
			current_map_[x][y] = active;
		}
	}
}

void GOL::flip_cell(int x, int y) {
	if (get_cell_state(x, y) == true) {
		change_cell(x, y, false);
	} else {
		change_cell(x, y, true);
	}
}

bool GOL::get_cell_state(int x, int y) {
	if (x < height_ && y < width_) { 
	return current_map_[x][y];
	} else {
	return 0;
	}
}

void GOL::update_map() {
	clear_new_map();
	int alive_neighbours = 0;

	for (int i = 0; i < height_; i++) {
		for (int j = 0; j < width_; j++) {

			for (int ii =- 1; ii <= 1; ii++) {
				for (int jj =- 1; jj <= 1; jj++) {					
					
					if (i + ii >= 0 && i + ii < height_ &&
							j + jj >= 0 && j + jj < width_ && 
							(ii != 0 || jj != 0)) {
					
						if (current_map_[i + ii][j + jj]) {
							alive_neighbours++;
						}
					}
				}
			}
			if (current_map_[i][j] == DEAD && alive_neighbours == 3) {
				new_map_[i][j] = true;
			}
			if (current_map_[i][j] == ALIVE && (alive_neighbours == 2 || alive_neighbours == 3)) {
				new_map_[i][j] = true;
			}

			alive_neighbours = 0;
		}
	}

	// // only for tests
	// for (int i = 0; i < height_; i++) {
	// 	for (int j = 0; j < width_; j++) {
	// 		std::cout << new_map_[i][j];
	// 	}
	// 	std::cout << "\n";
	// }

	current_map_ = new_map_;
}

void GOL::clear_new_map() {
	for (auto &row: new_map_) {
		std::fill(row.begin(), row.end(), false);
	}
}
