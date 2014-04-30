#ifndef BOARD
#define BOARD

#include "tetris_shapes.h"

struct Board {

	std::vector< std::vector<Tetris_Shape> > board;
	sf::RectangleShape Blank_Shape;
	BlankPiece blank;

	bool activeShape;
	
	//Standard member functions
	void create_board();
	void setPiece(Tetris_Shape &shape);
	void rotatePiece(Tetris_Shape &shape);
	void moveRight(Tetris_Shape &shape);
	void moveLeft(Tetris_Shape &shape);
	void updateBoard(Tetris_Shape &shape);
	void clearLine(int i);
	void setActivePiece(Tetris_Shape *shape);

	//Boolean functions
	bool isCollision(Tetris_Shape &shape);
	bool colBelow(Tetris_Shape &shape, int i, int j);
	bool colRight(Tetris_Shape &shape, int i, int j);
	bool colLeft(Tetris_Shape &shape, int i, int j);

	//Setup board array and on active shape.
	Board() :

		activeShape(false),
		board(32, std::vector<Tetris_Shape>(32))
	{}
};

#endif
