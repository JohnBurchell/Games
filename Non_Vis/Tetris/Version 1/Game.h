#include <SFML/Graphics.hpp>
#include "Board.h"


class Game {

public:

	//Variables.
	sf::RenderWindow window;
	std::vector<Tetris_Shape> shapes;
	Board boardObj;


	//Constructor.
	Game();

	//Memeber Methods.
	void run();
	void update();
	void draw();
	void drawBoard();
	void printBoard();
	void input(); // Gets user input.
};