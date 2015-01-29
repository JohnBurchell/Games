#include "tetris_shape.h"
#include "graphics.h"

Tetris_Shape::Tetris_Shape() :

x((Constants::BOARD_COLS / 2) - 2),
y(-2),
layout(4, std::vector<int>(4)),
first_coord(0, 0),
rotation(0),
colour(Colour::RED),
setable(true)

{
	change_rotation(0);
};

void Tetris_Shape::change_rotation(const int& new_rotation)
{
	assert(new_rotation >= 0);
	//Set the current rotation of the piece.
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			layout[i][j] = layouts[new_rotation][i][j];
		}
	}

	top_left();
	top_right();
	rotation = new_rotation;
}

std::pair<int, int> Tetris_Shape::top_left()
{
	//Reset the values.
	first_coord.first = 0;
	first_coord.second = 0;

	for (size_t i = 0; i < layout.size(); ++i){
		for (size_t j = 0; j < layout.size(); ++j){
			if (layout[j][i] != 0){
				first_coord.first = j;
				first_coord.second = i;

				return first_coord;
			}
		}
	}

	return first_coord;
}

std::pair<int, int> Tetris_Shape::top_right()
{
	//Reset the values.
	right_coord.first = 0;
	right_coord.second = 0;

	for (int i = 3; i >= 0; --i){
		for (size_t j = 0; j < layout[i].size(); ++j){
			if (layout[j][i] != 0){
				right_coord.first = j;
				right_coord.second = abs(i - 3);

				return right_coord;
			}
		}
	}

	return right_coord;
}

void Tetris_Shape::draw_current(Graphics& graphics)
{
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			//Draw only if it's a colour and has moved into the grid.
			if (layout[i][j] > 0 && y + i >= 0){
				//Create proper sizes for the drawing of the shapes.
				graphics.render_rectanlge(
					Constants::LEFT_INDENT + j * Constants::TILE_SIZE + (x * Constants::TILE_SIZE),
					Constants::LEFT_INDENT + i * Constants::TILE_SIZE + (y * Constants::TILE_SIZE),
					static_cast<int>(colour));
			}
		}
	}
}

void Tetris_Shape::draw_next(Graphics& graphics)
{
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			if (layout[i][j] > 0){
				//Create proper sizes for the drawing of the shapes.
				graphics.render_rectanlge(
					Constants::NEXT_SHAPE_INDENT + j * Constants::TILE_SIZE,
					Constants::LEFT_INDENT + i * Constants::TILE_SIZE,
					static_cast<int>(colour));
			}
		}
	}
}

Tetris_Shape::~Tetris_Shape() {}