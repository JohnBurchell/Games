#include "Board.h"


void Board::create_board() {

	for(auto& rows : board){
		for(auto& elems: rows) {
			elems = blank;
		}
	}
}

void Board::setPiece(Tetris_Shape &shape) {

	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++) {
			if(shape.layout[i][j] > 0) {

				board[shape.y + i][shape.x + j].piece = shape.piece;
				board[shape.y + i][shape.x + j].filled = true;
			}
		}
	}
}

/*
	Drop down pieces in the board by incrementing Y.

	Checks are performed after Y has been incremented.

	@Arguments: Pointer to active shape.

	Pointer required as i'm going to set the original to false incase it's hit the bottom.

*/

//Handle keyboard input


void Board::moveRight(Tetris_Shape &shape){

	//Check it's not on the edge
	if(shape.x < 16){
		shape.x++;

		if(isCollision(shape)) {
			shape.x--;
		}
	}
}

void Board::moveLeft(Tetris_Shape &shape){

	//Currently a bug here with the longs, it wont go over to the edge by two blocks when upright
	
	//Not on the edge!
	if(shape.x > 0){
		shape.x--;

		if(isCollision(shape)) {
			shape.x++;
		} 		
	}
}

bool Board::isCollision(Tetris_Shape &shape){

	//Check for collisions above and to the sides.

	bool collision = false;

	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++) {

			if(shape.layout[i][j] > 0 && (colLeft(shape, i , j)))
				return true;
			if(shape.layout[i][j] > 0 && (colRight(shape, i ,j)))
				return true;
			if(shape.layout[i][j] > 0 && (colBelow(shape, i, j)))
				return true;
		}
	}

	return false;
}

void Board::rotatePiece(Tetris_Shape &shape) {

	//Init 2d vectors
	std::vector < std::vector < int > > temp(4, std::vector<int>(4));
	std::vector < std::vector < int > > original(4, std::vector<int>(4));

	//Copy the layout into two temps.
	for(int i = 0; i < 4; i ++){
		for(int j = 0; j < 4; j++){
			if(shape.layout[i][j] > 0) {
				temp[3-j][i] = shape.layout[i][j];
				original[i][j]  = shape.layout[i][j];
			}
		}
	}

	//Make the change and change the shapes layout.
	for(int i = 0; i < 4; i ++){
		for(int j = 0; j < 4; j++){
			shape.layout[i][j] = temp[i][j];
		}
	}

	if(isCollision(shape)){
		//If collision occurs, revert. Else continue.
		for(int i = 0; i < 4; i ++){
			for(int j = 0; j < 4; j++){

			shape.layout[i][j] = original[i][j];
			}
		}
	}
}

bool Board::colBelow(Tetris_Shape &shape, int i, int j) {
	return (board[shape.y + i][shape.x + j].filled || shape.y + i >= 26);
}
bool Board::colLeft(Tetris_Shape &shape, int i, int j) {
	return ((board[shape.y + i][shape.x + j].filled) || shape.x + j <= 3);
}

bool Board::colRight(Tetris_Shape &shape, int i, int j) {
	return ((board[shape.y + i][shape.x + j].filled) || shape.x + j >= 16);
}

void Board::clearLine(int i){

	//Clear a line.
	for(int j = 0; j < 16; j++){
		board[i][j] = blank;
	}

	//Move all lines down one from the point where the line was cleared.
	for(i; i > 0; i--){
		for(int j = 0; j < 16; j++){
			board[i][j] = board[i - 1][j];
		}
	}
}



//TODO:
/*
	Rotation ------- Semi done, might improve this later on!.				--Half done
	Timer between dropping lines											-- DONE - will probably need some more tweaking from play throughs
	Global variables for Left, right bottom and top.
	check for a full line													-- DONE
	check for top line														-- DONE
	remove full line														-- DONE
	stop game on top line													-- DONE
	the bucket / border which the shapes collide / fall down in.            -- DONE
	speed increasing when more points accumilated                           -- DONE - Might need tweaking at some point
	show upcoming shape - maybe use a queue to have some fun with it?       -- DONE - Didn't use queue, no need
	Scores etc, stats and controls on the screen		

*/




