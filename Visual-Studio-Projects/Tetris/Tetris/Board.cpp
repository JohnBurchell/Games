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

	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++) {
			if(shape.layout[i][j] > 0) {

				board[shape.getY() + i][shape.getX() + j].piece = shape.piece;
				board[shape.getY() + i][shape.getX()+ j].setFilled(true);
			}
		}
	}
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

bool Board::colBelow(TetrisShape &shape, const int i, const int j) 
{
	return (board[shape.getY() + i][shape.getX() + j].isFilled() || shape.getY() + i >= 26);
}
bool Board::colLeft(TetrisShape &shape, const int i, const int j) 
{
	return ((board[shape.getY() + i][shape.getX() + j].isFilled()) || shape.getX() + j <= 3);
}

bool Board::colRight(TetrisShape &shape, const int i, const int j) 
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

