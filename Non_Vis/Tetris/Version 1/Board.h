#include "tetris_shapes.h"

struct Board {

	std::vector< std::vector<Tetris_Shape> > board;
	sf::RectangleShape Blank_Shape;
	Tetris_Shape *activeShape;

	int board2[16][16];

	void create_board();
	void CreateIntBoard();
	void setPiece(Tetris_Shape &shape);
	void rotatePiece();
	void stopRow(int i);
	void moveRight();
	void moveLeft();
	void updateBoard();
	void dropPieces();
	void removePosition();

	bool isActive(int i, int j);
	bool isGameOver();
	bool isWholeLine();

	Board() :

		board(16, std::vector<Tetris_Shape>(16))
	{}
};