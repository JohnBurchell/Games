#include "board.h"

class Graphics;

Board::Board() :

	board(16, std::vector<int>(10)),
	falling_shape(false),
	game_over(true)
{};

Board::~Board() {};

void Board::new_game()
{
	game_over = false;
	falling_shape = false;
	clear_board();
}

void Board::clear_board()
{
	for (auto& x : board){
		for (auto& y : x){
			y = 0;
		}
	}
}
void Board::set_piece(Tetris_Shape& shape)
{
	if (shape.y < 0){
		falling_shape = false;
		game_over = true;
		return;
	}

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (shape.layout[i][j] != 0){

				board[shape.y + i][shape.x + j] = static_cast<int>(shape.colour);
			}
		}
	}

	falling_shape = false;
}

/*
	Checks if the top row is empty, used to check for end-game conditions
*/

/*
	Right key pressed movement
	@argument Tetris_Shape
*/
void Board::move_right(Tetris_Shape &shape)
{
	++shape.x;

	if (shape.y < 0 || collision_right(shape)){
		--shape.x;
	}
}

void Board::move_left(Tetris_Shape &shape)
{
	--shape.x;

	if (shape.y < 0 || collision_left(shape)){
		++shape.x;
	}
}

bool Board::drop_pieces(Tetris_Shape& shape, const bool to_bottom)
{
	//Move down
	++shape.y;
	//If bottom or there is a collison, stop, else continue
	if (shape.y >= 0 && collision_below(shape) && shape.setable) {
		--shape.y;
		set_piece(shape);
		return false;
	}
	else if (shape.y >= 0 && collision_below(shape) && !shape.setable){
		--shape.y;
		return false;
	}

	if (to_bottom && shape.y >= 0 && !collision_below(shape)) {
		drop_pieces(shape, true);
	}
	return true;
}

bool Board::is_collision(Tetris_Shape &shape)
{
	bool result = false;

	if(shape.y < 0) {
		//Still falling from the outside the frame.
		return result;
	}

	if (collision_left(shape)){
		return true;
	}
	if (collision_right(shape)){
		return true;
	}
	if (collision_below(shape)){
		return true;
	}

	return result;
}

void Board::rotate_piece(Tetris_Shape &shape)
{
	//Increment current rotation
	int old_rotation = shape.rotation;
	int rotation_ = (shape.rotation + 1) % 4;
	//Set the new rotation
	shape.change_rotation(rotation_);

	if (is_collision(shape)){
		//If collision occurs, revert. Else continue.
		shape.change_rotation(old_rotation);
	}
}

bool Board::collision_below(Tetris_Shape& shape)
{
	for (int i = 0; i < 4; ++i){
		for (int j = 0; j < 4; ++j) {

			if (shape.layout[i][j] != 0){

				if (shape.y + i >= Constants::BOARD_ROWS){
					return true;
				}

				else if (board[shape.y + i][shape.x + j] != 0){
					return true;
				}
			}
		}
	}
	return false;
}

bool Board::collision_left(Tetris_Shape& shape)
{
	for (int i = 0; i < 4; ++i){
		for (int j = 0; j < 4; ++j) {

			if (shape.layout[i][j] != 0){

				if (shape.x + shape.first_coord.second < 0){
					return true;
				}

				if (shape.x + j >= Constants::BOARD_COLS){
					return true;
				}

				else if (board[shape.y + i][shape.x + j] != 0){
					return true;
				}
			}
		}
	}

	return false;
}

bool Board::collision_right(Tetris_Shape& shape)
{
	for (int i = 0; i < 4; ++i){
		for (int j = 0; j < 4; ++j) {

			if (shape.layout[i][j] != 0){

				if (shape.x + j > Constants::BOARD_COLS - 1){
					return true;
				}

				else if (board[shape.y + i][shape.x + j] != 0){
					return true;
				}
			}
		}
	}

	return false;
}

void Board::clear_line(int line)
{

	//Clear a line.
	for (auto& x : board[line]){
		x = 0;
	}

	//Move all lines down one block from the point where the line was cleared.
	for(int i = line; i > 0; i--){
		for (int j = 0; j < Constants::BOARD_COLS; j++){
			board[i][j] = board[i - 1][j];
		}
	}
}


/*
Draws the board by iterating through the vector.
*/

void Board::draw(Graphics& graphics)
{
	for (int i = 0; i < Constants::BOARD_ROWS; i++) {
		for (int j = 0; j < Constants::BOARD_COLS; j++) {
			if (board[i][j] > 0) {
				graphics.render_rectanlge(
					Constants::LEFT_INDENT + j * Constants::TILE_SIZE,
					Constants::LEFT_INDENT + i * Constants::TILE_SIZE,
					board[i][j]);
			}
		}
	}
}