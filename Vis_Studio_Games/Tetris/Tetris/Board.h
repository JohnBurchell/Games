#include "tetris_shapes.h"

struct Board {

	std::vector< std::vector<Tetris_Shape> > board2;
	sf::RectangleShape Blank_Shape;

	void create_board2();
	void setPiece(Tetris_Shape &shape);
	void removePosition();
	bool isGameOver();
	bool isWholeLine();

	Board() :

		board2(16, std::vector<Tetris_Shape>(16))
	{}
};