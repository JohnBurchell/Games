#include "tetris_shapes.h"

class Board {

public:

	std::vector< std::vector<Tetris_Shape> > board;
	sf::RectangleShape Blank_Shape;


	void create_board();
	void setPiece(Tetris_Shape &shape);
	void stopShape(Tetris_Shape &shape);
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