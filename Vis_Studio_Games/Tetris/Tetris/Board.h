#ifndef BOARD_H
#define BOARD_H

#include "TetrisShapes.h"
#include "TetrisShape.h"

class Board {

public :

	void create_board();
	std::vector< std::vector<TetrisShape> > board;
	sf::RectangleShape Blank_Shape;
	BlankPiece blank;

	Board();
	virtual ~Board();

	bool activeShape;

	//Standard member functions
	void setPiece(TetrisShape &shape);
	void rotatePiece(TetrisShape &shape);
	void moveRight(TetrisShape &shape);
	void moveLeft(TetrisShape &shape);
	void updateBoard(TetrisShape &shape);
	void clearLine(int i);
	void setActivePiece(TetrisShape *shape);

	//Boolean functions
	bool isCollision(TetrisShape &shape);
	bool colBelow(TetrisShape &shape, const int i, const int j);
	bool colRight(TetrisShape &shape, const int i, const int j);
	bool colLeft(TetrisShape &shape, const int i, const int j);


};

#endif
