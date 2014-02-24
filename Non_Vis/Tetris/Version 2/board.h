#include <SFML/Graphics.hpp>
#include <iostream>

class Board {

public:

	//Variables
	int board[20][16];

	//Constructor
	Board();

	//Methods
	void dropBlocks();
	void move();
	void rotate();
	void createBoard();
	//TODO
	void createBorder();

};

