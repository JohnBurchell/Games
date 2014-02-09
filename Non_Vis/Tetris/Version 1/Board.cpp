#include "Board.h"


void Board::create_board() {

	for(int i = 0; i < 16; i++) {
		for(int j = 0; j < 16; j++) {
			board[i][j] = blank;
		}
	}
}

void Board::setPiece(Tetris_Shape &shape) {

	activeShape = &shape;
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			if(shape.layout[i][j] > 0){
				//At i, j+7 until i change or make a global.
				shape.isFalling = true;
				board[i][j+7] = shape;
			}	
		}
	}
}

void Board::stopRow(int i) {
	//TODO - Make it so that it searches or finds the shape parts and stops them from falling.
	for(int i = 0; i < 16; i++){
		for(int j = 0; j < 16; j++){
			board[i][j].isFalling = false;
		}
	}

	activeShape = &blank;
}

void Board::dropPieces() {


	//TO-DO: 9th feb: Z and S shapes drop an extra block, fix!
	//Perhaps stop WHOLE line instead.
	for(int i = 15; i >= 0; i--) {
		for(int j = 15; j >= 0; j--) {
			//If falling and filled, moving
			//Make sure the bound check is in range.
			if((i+1 <= 15) && board[i][j].isFalling && !board[i+1][j].filled) {

				//Drop if not at bottom and not below is stopped.
				board[i+1][j] = board[i][j];
				board[i][j] = blank;
				board[i][j].isFalling = false;
			}

			else if(isActive(i, j)) {
				//Else it should be stopped.
				stopRow(i);
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
		rotatePiece(activeShape);
	}
}

void Board::moveRight(){
	//Move right
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

void Board::rotatePiece(Tetris_Shape *shape){

	//This is one of the worst things i think i've ever written.
	//Fuck this shit.
	
	//Find current active shapes that aren't the pivot
	//Make them blank.
	//Read rotated shape in?

	int previous_column, previous_row;
	int temp[4][4];
	int temp2[4][4] = {{0}};

	//Get current shape layout.
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			temp[i][j] = shape->layout[i][j];
		}
	}

	//Find where it starts on the board
	for(int i = 0; i < 16; i++){
		for(int j = 0; j < 16; j++){
			if(isActive(i,j)){
				previous_column = i;
				previous_row = j;
				break;
			}
		}
	}


	//This works for rotating, it makes a copy of the rotated position
	//By rotating the array (in a way).
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
				temp2[3-j][i] = temp[i][j];
		}

	}
		std::cout << "---Rotated---" << std::endl;


	//Clear all currently falling shapes
	for(int i = 0; i < 16; i++){
		for(int j = 0; j < 16; j++){
			if(isActive(i,j)){
				board[i][j].isFalling = false;
				board[i][j].filled = false;
			}
		}
	}

	//Re-assign new positions - Add collision checks here later
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			if(temp2[i][j] >= 1){
				shape->isFalling = true;
				shape->filled = true;
				board[previous_column + i][previous_row + j] = *shape;
			}
		}	
	}


	//Change the layout in the current shape for further rotates.
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			shape->layout[i][j] = temp2[i][j];
		}
	}
}



