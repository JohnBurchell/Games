//This will be the basic shapes that all the others inherit from.
//Idea is that the shapes are representations of 0 or 1 and the board is actually
//an array, when a line = 111111111 etc clear it, add score and continue.
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Tetris_Shape{

public:

	Tetris_Shape() : // Constructor
		//Initialize starting values.
		isFalling(false),
		filled(false),
		layout(4, std::vector<int>(4)),
		rotatedLayout(4, std::vector<int>(4)),
		size(30.f)
	{}

	virtual ~Tetris_Shape() {} //Destructor

	float size;
	bool isFalling, filled;
	int x,y;
	//Vector to hold it's layout
	std::vector< std::vector<int> > layout;
	std::vector< std::vector<int> > rotatedLayout;


	//Not using vectors for now, don't know how to use a 3d properly.
	//Perhaps refactor this at a later date.
	//A piece to hold the colour of the piece and to make it drawable.
	sf::RectangleShape piece;

};