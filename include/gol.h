#pragma once

#include <vector>

class GOL {
typedef std::vector<std::vector<bool>> Map;
const bool ALIVE = true;
const bool DEAD = false;

public:
	GOL(int width=0, int height=0);
	GOL& operator=(GOL &&new_GOL);
	void change_cell(int x, int y, bool active);
	void flip_cell(int x, int y);
	bool get_cell_state(int x, int y);
	void update_map();

private:
	int width_, height_;
	Map current_map_;
	Map new_map_;

	void create_map(int width, int height);
	void clear_new_map();
};
