#ifndef TetrisShape_H
#define TetrisShape_H

#include "common.h"

class Graphics;

//Consider adding a move constructor or a proper copy constructor?

class Tetris_Shape{

public:

	//Standard constructor
	Tetris_Shape();

	enum class Colour {
		NONE,
		RED,
		GREEN,
		BLUE,
		TEAL,
		ORANGE,
		YELLOW,
		PURPLE,
		TRANS
	};

	std::vector < std::vector<int> > layout;
	int layouts[4][4][4];
	
	void change_rotation(const int& new_rotation);

	std::pair < int, int > first_coord;
	std::pair < int, int > right_coord;

	int x, y, rotation;
	Colour colour;

	std::pair<int, int> top_left();
	std::pair<int, int> top_right();

	void draw_current(Graphics& graphics);
	void draw_next(Graphics& graphics);
	
	bool setable;

};

#endif