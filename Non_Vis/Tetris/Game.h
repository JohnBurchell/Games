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
	void Run();
	void Update();
	void Draw();
	void DrawBoard();
	void Input(); // Gets user input.
};