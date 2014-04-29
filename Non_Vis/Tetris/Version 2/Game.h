#include <SFML/Graphics.hpp>
#include "Board.h"


class Game {

public:

	Game();
	~Game();

	void run();

private:

	//Variables.
	sf::RenderWindow window;
	sf::Clock clock;
	sf::Time startTime;
	std::vector<Tetris_Shape> shapes;
	std::vector<sf::Text> guiText;
	//Parts of the border
	sf::RectangleShape left;
	sf::RectangleShape bottom;
	sf::RectangleShape right;
	//Next piece container
	sf::RectangleShape box_left;
	sf::RectangleShape box_bottom;
	sf::RectangleShape box_right;
	sf::RectangleShape box_top;

	//Board
	Board boardObj;

	int score, level, timer, lineCount;	

	//Current falling shape.
	Tetris_Shape currShape, nextShape;

	//Memeber Methods.
	void update();
	void draw();
	void drawBoard();
	void drawShape();
	void drawNextShape();
	void drawBorder();
	void createBox();
	void dropPieces();
	void printBoard();
	void randomPiece();
	void input();

	void gui();
	void updateGui();

	//Check if a line needs to be removed or not.
	void isWholeLine();
	bool emptyTopRow();
	bool dropTimer();

};