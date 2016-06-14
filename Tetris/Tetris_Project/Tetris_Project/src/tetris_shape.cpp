#include "tetris_shape.h"
#include <assert.h>
#include "graphics.h"

namespace
{
	constexpr int tile_size = 32;
	constexpr int left_indent = tile_size * 5;
	constexpr int next_shape_indent = tile_size * 16;
}

Tetris_Shape::Tetris_Shape(const int xPos, const int yPos, Colour colour) :

	m_x{xPos},
	m_y{yPos},
	m_layout( 4, std::vector<int>(4) ),
	m_first_coord{0, 0},
	m_rotation{0},
	m_colour{ colour },
	m_setable{true}
{
	change_rotation(0);

};

void Tetris_Shape::set_texture(Graphics& graphics)
{
	//Get pointer to shape block texture
	m_piece_texture = graphics.load_image("images/tetrominoe.png", true);
}

void Tetris_Shape::change_rotation(int new_rotation)
{
	assert(new_rotation >= 0);
	//Set the current rotation of the piece.
	for(int i = 0; i < 4; ++i) 
	{
		for(int j = 0; j < 4; ++j) 
		{
			m_layout[i][j] = m_layouts[new_rotation][i][j];
		}
	}

	top_left();
	top_right();
	m_rotation = new_rotation;
}

std::pair<int, int> Tetris_Shape::top_left()
{
	//Reset the values.
	m_first_coord.first = 0;
	m_first_coord.second = 0;

	for (size_t i = 0; i < m_layout.size(); ++i)
	{
		for (size_t j = 0; j < m_layout.size(); ++j)
		{
			if (m_layout[j][i] != 0)
			{
				m_first_coord.first = j;
				m_first_coord.second = i;

				return m_first_coord;
			}
		}
	}

	return m_first_coord;
}

std::pair<int, int> Tetris_Shape::top_right()
{
	//Reset the values.
	m_right_coord.first = 0;
	m_right_coord.second = 0;

	for (int i = 3; i >= 0; --i)
	{
		for (size_t j = 0; j < m_layout[i].size(); ++j)
		{
			if (m_layout[j][i] != 0)
			{
				m_right_coord.first = j;
				m_right_coord.second = abs(i - 3);

				return m_right_coord;
			}
		}
	}

	return m_right_coord;
}

void Tetris_Shape::draw_current(const Graphics& graphics)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			//Draw only if it's a colour and has moved into the grid.
			if (m_layout[i][j] > 0 && m_y + i >= 0)
			{
				//Create proper sizes for the drawing of the shapes.
				graphics.render_texture(*m_piece_texture, left_indent + (j * tile_size) + (m_x * tile_size), (i * tile_size) + (m_y * tile_size), static_cast<int>(m_colour));
			}
		}
	}
}

void Tetris_Shape::draw_next(const Graphics& graphics)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (m_layout[i][j] > 0)
			{
				//Create proper sizes for the drawing of the shapes.
				//The increments for i and j are added to create the spacing effect
				graphics.render_texture(*m_piece_texture, (next_shape_indent + (j * tile_size) + j), (left_indent + (i * tile_size) + i), static_cast<int>(m_colour));
			}
		}
	}
}
