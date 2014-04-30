//This will be the basic shapes that all the others inherit from.
//Idea is that the shapes are representations of 0 or 1 and the board is actually
//an array, when a line = 111111111 etc clear it, add score and continue.
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Tetris_Shape{

public:

	float size;
	bool isFalling, filled;
	int x,y;
	//Vector to hold it's layout
	std::vector< std::vector<int> > layout;
	//A piece to hold the colour of the piece and to make it drawable.
	sf::RectangleShape piece;

	void setLayout();
	
	Tetris_Shape() :
		//Initialize starting values.
		isFalling(false),
		filled(false),
		layout(4, std::vector<int>(2)),
		size(30.f)
	{}
};