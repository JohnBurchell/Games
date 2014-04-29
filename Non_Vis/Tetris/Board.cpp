#include "Board.h"

void Board::create_board() {

	BlankPiece blank;

	for(int i = 0; i < 16; i++) {
		for(int j = 0; j < 16; j++) {
			board[i][j] = blank;
		}
	}
}


void Board::setPiece(Tetris_Shape &shape) {
	int startpos = 7;
	int rowPost = 0;
	shape.isFalling = true;
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			if(shape.layout[i][j] > 0){
				board[rowPost][startpos] = shape;
				startpos++;
			}	
		}

		if(board[rowPost][startpos].filled == true || board[rowPost][startpos-1].filled == true) {
			rowPost++;
		}

		//Middle ground - Change later so that it takes the center.
		startpos=7;
	}
}

void Board::stopShape(Tetris_Shape &shape) {
	//TODO - Make it so that it searches or finds the shape parts and stops them from falling.
	std::cout << "I should be stopping now!" << std::endl;
	shape.isFalling = false;
}

void Board::dropPieces() {

	BlankPiece blank;
	for(int i = 15; i >= 0; i--) {
		for(int j = 15; j >= 0; j--) {
			//If falling and filled, moving
			if(board[i][j].isFalling && !board[i+1][j].filled) {

				//Change this to be the bottom, hard case to check if reached?
				if(i==14){
					stopShape(board[i][j]);
				}

				//Drop if not at bottom and not below is stopped.
				board[i+1][j] = board[i][j];
				board[i][j] = blank;
				board[i][j].isFalling = false;
			}

			else if(isActive(i, j)) {
				//Else it should be stopped.
				stopShape(board[i][j]);
			}

			//Implicit else - They are otherwise a blank block.
		}
	}
}

void Board::updateBoard(){

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		//Move left
		std::cout << "Left was pressed " << std::endl;
		moveLeft();
	}

	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		//Move right
		std::cout << "Right was pressed " << std::endl;
		moveRight();	
	}

	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){

		std::cout << "Down was pressed " << std::endl;
	}

	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){

		std::cout << "Up was pressed " << std::endl;
	}
}

void Board::moveRight(){
	//Move right
	BlankPiece blank;

	for(int i = 15; i >= 0; i--) {
		for(int j = 15; j >= 0; j--) {
			if(board[i][j].isFalling && board[i][j].filled){
				//Add offset to j or Y axis and move accordingly.
				board[i][j + 1] = board[i][j];
				board[i][j] = blank;
				board[i][j].isFalling = false;
			}
		}
	}
}

void Board::moveLeft(){
	//Move left
	BlankPiece blank;

	for(int i = 15; i >= 0; i--) {
		for(int j = 15; j >= 0; j--) {
			if(isActive(i, j)){
				//Add offset to j or Y axis and move accordingly.
				if(j > 2 && isActive(i, j - 1)) {
					//If the block to the left is active
					board[i][j - 2] = board[i][j - 1];
				}
				board[i][j - 1] = board[i][j];
				board[i][j] = blank;
				board[i][j].isFalling = false;

				break;
			}
		}
	}
}

bool Board::isActive(int i, int j){

	return (board[i][j].isFalling && board[i][j].filled);
}




