#include <SFML/Graphics.hpp>
#include "board.h"

class Game {

public:

	//Variables.
	sf::RenderWindow window;
	bool playing;
	Board board;

	//Constructor.
	Game();

	//Memeber Methods.
	void run();
	void update();
	void createBoard();
	void draw();
	void drawBoard();
	void input(); // Gets user input.

	//For debugging
	void printBoard();

};