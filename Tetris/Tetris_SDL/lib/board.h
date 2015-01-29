#ifndef BOARD_H
#define BOARD_H
#pragma once

#include "tetris_shape.h"
#include "graphics.h"

class Graphics;

class Board {

public :
	
	Board();
	~Board();

	void new_game();

	std::vector< std::vector<int> > board;

	bool falling_shape;

	void rotate_piece(Tetris_Shape& shape);
	bool drop_pieces(Tetris_Shape& shape, const bool to_botom);
	void move_right(Tetris_Shape& shape);
	void move_left(Tetris_Shape& shape);
	void set_piece(Tetris_Shape& shape);
	void clear_line(int i);

	//Collision detection
	bool is_collision(Tetris_Shape& shape);
	bool collision_below(Tetris_Shape& shape);
	bool collision_right(Tetris_Shape& shape);
	bool collision_left(Tetris_Shape& shape);

	bool game_over;

	void draw(Graphics& graphics);

private:
	void clear_board();

};

#endif
