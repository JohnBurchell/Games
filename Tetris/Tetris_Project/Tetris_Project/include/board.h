#ifndef BOARD_H
#define BOARD_H
#pragma once

class Graphics;
class Tetris_Shape;

#include <vector>
#include <SDL.h>
#include <memory>

class Board {

public :
	
	Board(Graphics& graphics, const int cols, const int rows, const int tile_size);

	//Disable copying
	Board(const Board& rhs) = delete;
	Board operator=(const Board& rhs) = delete;

	void new_game();

	std::vector< std::vector<int> > board;

	bool falling_shape;

	void rotate_piece(Tetris_Shape& shape);
	bool drop_pieces(Tetris_Shape& shape, const bool to_botom);
	void move_right(Tetris_Shape& shape);
	void move_left(Tetris_Shape& shape);
	void set_piece(const Tetris_Shape& shape);
	void clear_line(int i);

	//Collision detection
	bool is_collision(const Tetris_Shape& shape);
	bool collision_below(const Tetris_Shape& shape);
	bool collision_right(const Tetris_Shape& shape);
	bool collision_left(const Tetris_Shape& shape);

	bool game_over;

	void draw(const Graphics& graphics);

private:
	void clear_board();
	
	const int m_rows;
	const int m_cols;
	const int m_tile_size;

	std::shared_ptr<SDL_Texture*> m_set_piece_texture;

};

#endif
