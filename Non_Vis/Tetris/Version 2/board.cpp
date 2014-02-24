#include "board.h"
#include "shapes.h"

Board::Board(){

	//Create the board.
}

void Board::createBoard(){

	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 16; j++){
			//Make -1, aka blank.
			board[i][j] = -1;
		}
	}

	std::cout << "Created board." << std::endl;
}


void Board::createBorder(){

	std::cout << "Creating border" << std::endl;
}