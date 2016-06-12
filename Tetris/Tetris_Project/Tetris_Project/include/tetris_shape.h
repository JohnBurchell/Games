#ifndef TetrisShape_H
#define TetrisShape_H

#include <vector>
#include <memory>

class Graphics;
struct SDL_Texture;

class Tetris_Shape
{

public:
	enum class Colour 
	{
		NONE,
		RED,
		GREEN,
		BLUE,
		TEAL,
		ORANGE,
		YELLOW,
		PURPLE,
		TRANS
	};

	using Coord_Pair = std::pair<int, int>;
	using Layout_Vec = std::vector<std::vector<int>>;

	//Standard constructor
	Tetris_Shape(const int xPos, const int yPos, Colour = Colour::RED);

	void change_rotation(int new_rotation);
	
	std::pair<int, int> top_left();
	std::pair<int, int> top_right();

	void draw_current(const Graphics& graphics);
	void draw_next(const Graphics& graphics);

	void setable(const bool value) { m_setable = value; };
	bool setable() const { return m_setable; };
	void colour(const Tetris_Shape::Colour colour) { m_colour = colour; };
	int colour() const { return static_cast<int>(m_colour); };

	inline const Layout_Vec& layout() const { return m_layout; };
	
	inline const int x() const { return m_x; };
	void x(const int x) { m_x = x; };
	inline const int y() const { return m_y; };
	void y(const int y) { m_y = y; };

	inline const int rotation() const { return m_rotation; };

	Coord_Pair first_coord() const { return m_first_coord; };
	Coord_Pair right_coord() const { return m_right_coord; };
	
	int m_layouts[4][4][4];

	void set_texture(Graphics& graphics);
	
private:

	Layout_Vec m_layout;
	Coord_Pair m_first_coord;
	Coord_Pair m_right_coord;

	std::shared_ptr<SDL_Texture*> m_piece_texture;

	int m_x;
	int m_y;
	int m_rotation;

	Colour m_colour;
	bool m_setable;

};

#endif