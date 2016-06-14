#include "board.h"
#include "graphics.h"
#include "tetris_shape.h"

namespace
{
	constexpr int left_indent = 32 * 5;
}

Board::Board(Graphics& graphics, const int cols, const int rows, const int tile_size) :

	board(rows, std::vector<int>(cols)),
	falling_shape(false),
	game_over(true),
	m_cols(cols),
	m_rows(rows),
	m_tile_size(tile_size)
{
	m_set_piece_texture = graphics.load_image("images/tetrominoe.png", true);
};

void Board::new_game()
{
	game_over = false;
	falling_shape = false;
	clear_board();
}

void Board::clear_board()
{
	for (auto& x : board)
	{
		for (auto& y : x)
		{
			y = 0;
		}
	}
}
void Board::set_piece(const Tetris_Shape& shape)
{
	if (shape.y() <= 0)
	{
		//Piece is trying to be set outside the top border of the board
		falling_shape = false;
		game_over = true;
		return;
	}

	for (int i = 0; i < 4; ++i) 
	{
		for (int j = 0; j < 4; ++j) 
		{
			if (shape.layout()[i][j] != 0)
			{
				board[shape.y() + i][shape.x() + j] = shape.colour();
			}
		}
	}

	falling_shape = false;
}

/*
	Right key pressed movement
	@argument Tetris_Shape
*/
bool Board::move_right(Tetris_Shape &shape)
{
	shape.x(shape.x() + 1);

	if (collision_right(shape))
	{
		shape.x(shape.x() - 1);
		return false;
	}

	return true;
}

bool Board::move_left(Tetris_Shape &shape)
{
	shape.x(shape.x() - 1);

	if (collision_left(shape))
	{
		shape.x(shape.x() + 1);
		return false;
	}

	return true;
}

bool Board::drop_pieces(Tetris_Shape& shape, const bool to_bottom)
{
	//Move down
	shape.y(shape.y() + 1);

	//If bottom or there is a collison, stop, else continue
	if (shape.y() >= 0 && collision_below(shape) && shape.setable()) 
	{
		shape.y(shape.y() - 1);
		set_piece(shape);
		return false;
	}
	else if (shape.y() >= 0 && collision_below(shape) && !shape.setable())
	{
		shape.y(shape.y() - 1);
		return false;
	}

	if (to_bottom && shape.y() >= 0 && !collision_below(shape)) 
	{
		drop_pieces(shape, true);
	}
	return true;
}

bool Board::is_collision(const Tetris_Shape &shape)
{
	bool result = false;

	if (collision_left(shape))
	{
		return true;
	}
	if (collision_right(shape))
	{
		return true;
	}
	if (collision_below(shape))
	{
		return true;
	}

	return result;
}

void Board::rotate_piece(Tetris_Shape &shape)
{
	//Increment current rotation
	int old_rotation = shape.rotation();
	int rotation_ = (shape.rotation() + 1) % 4;
	//Set the new rotation
	shape.change_rotation(rotation_);

	if (is_collision(shape))
	{
		//If collision occurs, revert. Else continue.
		shape.change_rotation(old_rotation);
	}
}

bool Board::collision_below(const Tetris_Shape& shape)
{
	int x = shape.x();
	int y = shape.y();

	if (y < 0)
	{
		//Shape is still outside the box - don't need to check
		return false;
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j) 
		{

			if (shape.layout()[i][j] != 0)
			{

				if (y + i >= m_rows)
				{
					return true;
				}

				else if (board[y + i][x + j] != 0)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Board::collision_left(const Tetris_Shape& shape)
{
	int x = shape.x();
	int y = shape.y();

	if (y < 0)
	{
		if (x < 0)
		{
			return true;
		}

		return false;
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j) 
		{
			if (shape.layout()[i][j] != 0)
			{
				if (x + shape.first_coord().second < 0)
				{
					return true;
				}

				if (x + j >= m_cols)
				{
					return true;
				}

				else if (board[y + i][x + j] != 0)
				{
					return true;
				}
			}
		}
	}

	return false;
}

bool Board::collision_right(const Tetris_Shape& shape)
{
	int y = shape.y();
	int x = shape.x();

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j) 
		{
			if (shape.layout()[i][j] != 0)
			{
				if (shape.x() + j >= m_cols)
				{
					return true;
				}

				if (shape.y() + i < 0)
				{
					return true;
				}

				else if (board[shape.y() + i][shape.x() + j] != 0)
				{
					return true;
				}
			}
		}
	}

	return false;
}

void Board::clear_line(int i)
{

	//Clear a line.
	for (auto& x : board[i])
	{
		x = 0;
	}

	//Move all lines down one block from the point where the line was cleared.
	for(i; i > 0; --i)
	{
		for (int j = 0; j < m_cols; ++j)
		{
			board[i][j] = board[i - 1][j];
		}
	}
}


/*
Draws the board by iterating over the locations.
*/

void Board::draw(const Graphics& graphics)
{
	for (int i = 0; i < m_rows; ++i) 
	{
		for (int j = 0; j < m_cols; ++j) 
		{
			if (board[i][j] > 0) 
			{
				graphics.render_texture(*m_set_piece_texture, left_indent + (j * m_tile_size), (i * m_tile_size), board[i][j]);
			}
		}
	}

	//Create outline
	graphics.render_outline(m_rows, m_cols, m_tile_size, left_indent);
}