#ifndef BOARD_H
#define BOARD_H

#include "TetrisShapes.h"
#include "TetrisShape.h"

class Board {

public :
	
	Board();
	~Board();

	void create_board();
	std::vector< std::vector<TetrisShape> > board;
	sf::RectangleShape Blank_Shape;
	BlankPiece blank;
	bool activeShape;

	void rotatePiece(TetrisShape &shape);
	void moveRight(TetrisShape &shape);
	void moveLeft(TetrisShape &shape);
	void setPiece(TetrisShape &shape);
	void clearLine(int i);


	bool emptyTopRow();
	bool isCollision(TetrisShape &shape);
	bool colBelow(TetrisShape &shape, const int &i, const int &j);
	bool colRight(TetrisShape &shape, const int &i, const int &j);
	bool colLeft(TetrisShape &shape, const int &i, const int &j);


};

#endif
