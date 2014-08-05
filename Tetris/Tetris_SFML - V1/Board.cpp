#include "Board.h"

Board::Board() :

		activeShape(false),
		board(32, std::vector<TetrisShape>(32))

	{}

Board::~Board() {}

void Board::create_board() 
{

	for(auto& rows : board){
		for(auto& elems: rows) {
			elems = blank;
		}
	}
}

void Board::setPiece(TetrisShape &shape) 
{
	bool placed = true;

	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++) {
			if(shape.layout[i][j] > 0 ) {
				if(shape.getY() + i >= 0 && shape.getX() >= 0) {
					board[shape.getY() + i][shape.getX() + j].piece = shape.piece;
					board[shape.getY() + i][shape.getX()+ j].setFilled(true);
				}
			}
		}
	}
}

/*
	Checks if the top row is empty, used to check for end-game conditions
*/

bool Board::emptyTopRow()
{
	for(int j = 0; j < 16; j ++){
		if(board[0][j].isFilled()){
			return false;
		}
	}
	return true;
}


/*
	Right key pressed movement
	@argument Tetris_Shape
*/
void Board::moveRight(TetrisShape &shape)
{

	//Check it's not on the edge
	int x = shape.getX();

	if(x < 16){
		shape.setX(++x);

		if(isCollision(shape)) {
			shape.setX(--x);
		}
	}
}

void Board::moveLeft(TetrisShape &shape)
{

	//Currently a bug here with the longs, it wont go over to the edge by two blocks when upright
	
	//Not on the edge!
	int x = shape.getX();

	if(x > 0){
		shape.setX(--x);

		if(isCollision(shape)) {
			shape.setX(++x);
		} 		
	}
}

bool Board::isCollision(TetrisShape &shape)
{

	//Check for collisions above and to the sides.

	if(shape.getY() < 0) {

		//Still falling from the outside the frame.
		return false;
	}

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

void Board::rotatePiece(TetrisShape &shape) 
{

	//Increment current rotation
	int rotation = (shape.getRotation() + 1) % 4;
	//Set the new rotation
	shape.changeRotation(rotation);
	shape.setRotation(rotation);

	if(isCollision(shape)){
		//If collision occurs, revert. Else continue.
		for(int i = 0; i < 4; i ++){
			for(int j = 0; j < 4; j++){

			shape.layout[i][j] = shape.layouts[rotation - 1][i][j];
			}
		}
	}
}

bool Board::colBelow(TetrisShape &shape, const int &i, const int &j) 
{
	return (board[shape.getY() + i][shape.getX() + j].isFilled() || shape.getY() + i >= 26);
}

bool Board::colLeft(TetrisShape &shape, const int &i, const int &j) 
{
	return ((board[shape.getY() + i][shape.getX() + j].isFilled()) || shape.getX() + j <= 3);
}

bool Board::colRight(TetrisShape &shape, const int &i, const int &j) 
{
	return ((board[shape.getY() + i][shape.getX() + j].isFilled()) || shape.getX() + j >= 16);
}

void Board::clearLine(int i)
{

	//Clear a line.
	for(int j = 0; j < 16; j++){
		board[i][j] = blank;
	}

	//Move all lines down one block from the point where the line was cleared.
	for(i; i > 0; i--){
		for(int j = 0; j < 16; j++){
			board[i][j] = board[i - 1][j];
		}
	}
}

