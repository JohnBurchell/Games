#include "game.h"
#include "graphics.h"
#include "common.h"
#include "g_interface.h"
#include <sstream>
#include <ctime>
#include <fstream>
#include <memory>

using namespace std::chrono;

Game::Game() :

score(0),
level(1),
line_count(0),
pause_duration(0),
total_time(0),
new_game(true),
player_name(" "),
current_state(Game_State::MAIN_MENU)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	srand(static_cast<unsigned int>(time(nullptr)));
	ghost_shape.setable = false;
	create_shapes();
	run();
}

void Game::start_new_game()
{
	board.new_game();
	random_piece();
	current_shape = next_shape;
	random_piece();
	pause_duration = 0;
	line_count = 0;
	score = 0;
	timer = 0;
	level = 0;
	time_taken = 0;
	game_start = std::chrono::system_clock::now();
	//Cannot send an empty string to the UI when collecting the player name.
	player_name = " ";
	new_game = true;
}


void Game::run()
{
	Graphics graphics;
	Sound sound;

	G_Interface main_menu (graphics);
	main_menu.setup_main_menu(graphics);
	menus.emplace("Main", main_menu);

	G_Interface pause_menu(graphics);
	pause_menu.setup_pause(graphics);
	menus.emplace("Pause", pause_menu);

	G_Interface scoreboard(graphics);
	scoreboard.setup_scoreboard(graphics);
	menus.emplace("High_Score", scoreboard);

	G_Interface scoring_screen(graphics);
	scoring_screen.setup_scoring(graphics);
	menus.emplace("Score", scoring_screen);

	G_Interface play_screen(graphics);
	menus.emplace("Play_Screen", play_screen);

	float previous_frame = 0.0f;

	bool playing = true;

	current_state = Game_State::MAIN_MENU;

	int frames_passed = 0;

	while (playing) 
	{

		frame_start = Clock::now();

		if (new_game)
		{
			start_new_game();
		}

		//Get start time.
		const Uint32 start_time = SDL_GetTicks();

		std::string player_name;

		switch (current_state)
		{
		case Game_State::MAIN_MENU:
			sound.stop_music();
			break;

		case Game_State::PLAYING:
			//Get start time.
			if (new_game) 
			{
				//Start of a new game
				sound.play_music();
				game_start = std::chrono::system_clock::now();
				new_game = false;
			}
			else if (Mix_PausedMusic())
			{
				pause_end = Clock::now();
				pause_duration += duration_cast<seconds>(pause_end - pause_start).count();
				sound.unpause_music();
			}
			//If the current shape is empty, it means there's nothing active.
			if (!board.falling_shape) 
			{
				current_shape = next_shape;
				ghost_shape = next_shape;
				ghost_shape.colour = Tetris_Shape::Colour::TRANS;
				ghost_shape.setable = false;
				board.falling_shape = true;
				random_piece();

				//Reset start time of new shape.
				fall_timer = Clock::now();
			}

			if (board.game_over)
			{
				current_state = Game_State::SCORING;
			}

			total_time = static_cast<int>(duration_cast<seconds>(Clock::now() - game_start).count() - pause_duration);
			pause_start = Clock::now();
			break;

		case Game_State::PAUSED:
			sound.pause_music();
			break;

		case Game_State::SCORING:
			sound.stop_music();
			break;

		case Game_State::HIGH_SCORE:
			break;

		case Game_State::FINISHED:
			exit(0);
		default:
			std::cout << "UKNOWN STATE!" << std::endl;
			break;
		}
		
		input();
		update();
		draw(graphics);

		//Calculate fps, set title to show the most recent frame time / fps.
		frame_end = Clock::now();
		time_taken = total_time;
	}
}
/*
	Draws the following elements:

	Clears the board
	Board
	Falling shape
	Border
	Next shape
	UI elements
	
	Then displays the window
*/

void Game::draw(Graphics& graphics)
{
	graphics.clear();
	if (current_state == Game_State::PLAYING || current_state == Game_State::PAUSED) 
	{
		current_shape.draw_current(graphics);
		//ghost_shape.draw_current(graphics);
		next_shape.draw_next(graphics);
		board.draw(graphics);
		graphics.render_outline();
	}
	gui(graphics);
	graphics.flip();
}

/*
	Drops pieces of alloted time has passed and checks for whole lines.
*/

void Game::update() 
{
	//If enough time has passed, drop blocks.
	if(current_state == Game_State::PLAYING && drop_timer())
	{
		board.drop_pieces(current_shape, false);
		//ghost_shape.x = current_shape.x;
		//ghost_shape.y = current_shape.y;
		//ghost_shape.change_rotation(current_shape.rotation);
		board.drop_pieces(ghost_shape, true);
	}
	is_whole_line();
}


void Game::input()
{
	/*Handles the input, moving and rotating shpaes when need be.*/
	SDL_Event event;
    while(SDL_PollEvent(&event))
    {
		if (current_state == Game_State::PLAYING) 
		{
			//If cross clicked, exit.
			switch (event.type)
			{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) 
				{
				case SDLK_ESCAPE:
					current_state = Game_State::PAUSED;
					break;
				case SDLK_LEFT:
					board.move_left(current_shape);
					ghost_shape.x = current_shape.x;
					break;
				case SDLK_RIGHT:
					board.move_right(current_shape);
					ghost_shape.x = current_shape.x;
					break;
				case SDLK_UP:
					board.rotate_piece(current_shape);
					ghost_shape.change_rotation(current_shape.rotation);
					break;
				case SDLK_DOWN:
					board.drop_pieces(current_shape, false);
					break;
				case SDLK_SPACE:
					board.drop_pieces(current_shape, true);
					break;
				}
			}
		}

		else if (current_state == Game_State::PAUSED)
		{
			if (event.type == SDL_KEYDOWN) 
			{
				switch (event.key.keysym.sym) 
				{
				case SDLK_ESCAPE:
					current_state = Game_State::PLAYING;
					break;
				}
			}
			for (auto& x : menus["Pause"].buttons)
			{
				std::string result = x.handle_event(&event);
				if (result != "no_action") 
				{
					if (result == "Play")
					{
						current_state = Game_State::PLAYING;
					}
					else if (result == "Main")
					{
						new_game = true;
						current_state = Game_State::MAIN_MENU;
					}
					else if (result == "Exit")
					{
						current_state = Game_State::FINISHED;
					}
				}
			}
		}

		else if (current_state == Game_State::MAIN_MENU)
		{
			for (auto& x : menus["Main"].buttons)
			{
				std::string result = x.handle_event(&event);
				if (result != "no_action") 
				{

					if (result == "Play")
					{
						start_new_game();
						current_state = Game_State::PLAYING;
					}
					else if (result == "Score")
					{
						current_state = Game_State::HIGH_SCORE;
					}
					else if (result == "Exit")
					{
						current_state = Game_State::FINISHED;
					}
				}
			}
		}

		else if (current_state == Game_State::HIGH_SCORE)
		{
			for (auto& x : menus["High_Score"].buttons)
			{
				std::string result = x.handle_event(&event);
				if (result != "no_action") 
				{

					if (result == "Main")
					{
						current_state = Game_State::MAIN_MENU;
					}
					else if (result == "Exit")
					{
						current_state = Game_State::FINISHED;
					}
				}
			}
		}
		else if (current_state == Game_State::SCORING) 
		{
			for (auto& x : menus["Score"].buttons)
			{
				std::string result = x.handle_event(&event);
				if (result != "no_action") 
				{
					SDL_StopTextInput();

					if (result == "Main")
					{
						current_state = Game_State::MAIN_MENU;
					}
					else if (result == "Exit")
					{
						current_state = Game_State::FINISHED;
					}
				}
			}
			if (!SDL_IsTextInputActive())
			{
				SDL_StartTextInput();
			}
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_BACKSPACE && player_name.length() > 1)
				{
					player_name.pop_back();
				}
				else if (event.key.keysym.sym == SDLK_BACKSPACE && player_name.length() <= 1)
				{
					player_name.pop_back();
					player_name += " ";
				}
				else if (event.key.keysym.sym == SDLK_RETURN)
				{
					if (player_name.length() <= 0) 
					{
						save_player("NO_NAME");
					}
					save_player(player_name);
					SDL_StopTextInput();
					current_state = Game_State::HIGH_SCORE;
				}
			}
			else if (event.type == SDL_TEXTINPUT)
			{
				if (!((event.text.text[0] == 'c' || event.text.text[0] == 'C') && (event.text.text[0] == 'v' || event.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL)) 
				{
					if (player_name == " ")
					{
						//Remove blank space.
						player_name.pop_back();
					}
					player_name += event.text.text;
				}
			}
		}
    }
}

/*
	Randomises a piece from the vector or tetris_shape objects
	It sets the piece in the middle of screen (currently at X 7)
*/

void Game::random_piece()
{
	next_shape = *shapes[rand() % shapes.size()];
}

/*
	Checks if the line is full, i.e. the sum of the whole line is 
	equal to a certain number. For now, that number is 12.
*/
void Game::is_whole_line()
{
	//Sum for calculating a whole line.
	int sum;

	for (int i = 0; i < Constants::board_rows; ++i) 
	{
		sum = 0;
		for (int j = 0; j < Constants::board_cols; ++j) 
		
		{
			if(board.board[i][j] > 0) 
			{
				sum++;
			}
		}

		if(sum == Constants::board_cols) 
		{
			board.clear_line(i);
			score += 10;
			line_count++;
			//If it's divisible by 3 again, another 3 lines have been reached so
			//The level goes up.
			if (line_count % 3 == 0) 
			{
				level++;
			}
		}
	}
}

/*
	Timer to check if a piece needs to drop down a line or not
	Currently calculated as:

	1 second - level * 20

	Level 1 is .5 of a second
*/

bool Game::drop_timer()
{
	duration<double> life_time = milliseconds(500 - ((level - 1) * 20));

	//Force the speed to remain positive if it's gone below 0.0
	if(life_time.count() <= 0.0) 
	{
		life_time = milliseconds(100);
	}

	if (Clock::now() >= fall_timer + life_time)
	{
		//Reset time to current time
		fall_timer = Clock::now();
		return true;
	} 

	return false;
}

std::string Game::calc_time(uint64_t time_taken)
{
	std::stringstream stream;
	if (time_taken >= 60) 
	{
		//Perform clipping
		uint64_t mins = 0, secs = 0;
		mins = time_taken / 60;
		secs = time_taken % 60;
		stream << mins << ":";
		if (secs < 10)
		{
			stream << "0";
		}
		stream << secs;
	}
	else 
	{
		stream << "0:";
		if (time_taken < 10)
		{
			stream << "0";
		}
		stream << time_taken;
	}
	return stream.str();
}


/*
	Responsible for drawing the basic ui elements.
*/

void Game::gui(Graphics& graphics)
{
	if (current_state == Game_State::MAIN_MENU) 
	{
		menus["Main"].render_ui(graphics);
	}
	else if (current_state == Game_State::SCORING) 
	{
		std::map<std::string, std::string> values;

		values["Score"] = std::to_string(score);
		values["Lines"] = std::to_string(line_count);
		values["Level"] = std::to_string(level);
		values["Player_Name"] = player_name;

		menus["Score"].update(values);
		menus["Score"].render_ui(graphics);

	}
	else if (current_state == Game_State::HIGH_SCORE) 
	{
		std::map<std::string, std::string> values;

		menus["High_Score"].render_ui(graphics);
	}
	//Else we're playing
	else 
	{
		std::map<std::string, std::string> values;

		//Locations are given in terms of tile size, 32
		values["Time_Taken"] = calc_time(time_taken);
		values["Score"] = std::to_string(score);
		values["Lines"] = std::to_string(line_count);

		menus["Play_Screen"].update(values);
		menus["Play_Screen"].render_ui(graphics);

		if (current_state == Game_State::PAUSED)
		{
			menus["Pause"].render_ui(graphics);
		}
	}
}

void Game::save_player(const std::string& name)
{
	std::ofstream file;
	file.open("players.dat", std::ios::out | std::ios::app);
	file << name << "," << score << "-" << line_count << ";" << "\n";
	file.close();
}



void Game::create_shapes() {

	//First, define the layouts of the shapes.
	int rotations[7][4][4][4] = {

	//Cube
	{
		/*Rotation 1*/
		{ { 0,0,0,0 },
		  { 0,1,1,0 },
		  { 0,1,1,0 },
		  { 0,0,0,0 }},
		/*Rotation 2*/
		{ { 0,0,0,0 },
		  { 0,1,1,0 },
		  { 0,1,1,0 },
		  { 0,0,0,0 }},
		/*Rotation 3*/
		{ { 0,0,0,0 },
		  { 0,1,1,0 },
		  { 0,1,1,0 },
		  { 0,0,0,0 }},
		/*Rotation 4*/
		{ { 0,0,0,0 },
		  { 0,1,1,0 },
		  { 0,1,1,0 },
		  { 0,0,0,0 }}
	},

	//Straight
	{
		/*Rotation 1*/
		{ { 0,0,0,0 },
		  { 1,1,1,1 },
		  { 0,0,0,0 },
		  { 0,0,0,0 }},
		/*Rotation 2*/
		{ { 0,0,1,0 },
		  { 0,0,1,0 },
		  { 0,0,1,0 },
		  { 0,0,1,0 }},
		/*Rotation 3*/
		{ { 0,0,0,0 },
		  { 0,0,0,0 },
		  { 1,1,1,1 },
		  { 0,0,0,0 }},
		/*Rotation 4*/
		{ { 0,1,0,0 },
		  { 0,1,0,0 },
		  { 0,1,0,0 },
		  { 0,1,0,0 }}
	},
	
	//SZhape
	{
		/*Rotation 1*/
		{ { 0,1,1,0 },
		  { 1,1,0,0 },
		  { 0,0,0,0 },
		  { 0,0,0,0 }},
		/*Rotation 2*/
		{ { 0,1,0,0 },
		  { 0,1,1,0 },
		  { 0,0,1,0 },
		  { 0,0,0,0 }},
		/*Rotation 3*/
		{ { 0,0,0,0 },
		  { 0,1,1,0 },
		  { 1,1,0,0 },
		  { 0,0,0,0 }},
		/*Rotation 4*/
		{ { 1,0,0,0 },
		  { 1,1,0,0 },
		  { 0,1,0,0 },
		  { 0,0,0,0 }}
	},
	
	//ZShape
	{
		/*Rotation 1*/
		{ { 1,1,0,0 },
		  { 0,1,1,0 },
		  { 0,0,0,0 },
		  { 0,0,0,0 }},
		/*Rotation 2*/
		{ { 0,0,1,0 },
		  { 0,1,1,0 },
		  { 0,1,0,0 },
		  { 0,0,0,0 }},
		/*Rotation 3*/
		{ { 0,0,0,0 },
		  { 1,1,0,0 },
		  { 0,1,1,0 },
		  { 0,0,0,0 }},
		/*Rotation 4*/
		{ { 0,1,0,0 },
		  { 1,1,0,0 },
		  { 1,0,0,0 },
		  { 0,0,0,0 }}
	},

	//T shape
	{
		/*Rotation 1*/
		{ { 0,1,0,0 },
		  { 1,1,1,0 },
		  { 0,0,0,0 },
		  { 0,0,0,0 }},
		/*Rotation 2*/
		{ { 0,1,0,0 },
		  { 0,1,1,0 },
		  { 0,1,0,0 },
		  { 0,0,0,0 }},
		/*Rotation 3*/
		{ { 0,0,0,0 },
		  { 1,1,1,0 },
		  { 0,1,0,0 },
		  { 0,0,0,0 }},
		/*Rotation 4*/
		{ { 0,1,0,0 },
		  { 1,1,0,0 },
		  { 0,1,0,0 },
		  { 0,0,0,0 }}
	},
	
	//Normal L
	{

		/*Rotation 1*/
		{ { 0,0,1,0 },
		  { 1,1,1,0 },
		  { 0,0,0,0 },
		  { 0,0,0,0 }},
		/*Rotation 2*/
		{ { 0,1,0,0 },
		  { 0,1,0,0 },
		  { 0,1,1,0 },
		  { 0,0,0,0 }},
		/*Rotation 3*/
		{ { 0,0,0,0 },
		  { 1,1,1,0 },
		  { 1,0,0,0 },
		  { 0,0,0,0 }},
		/*Rotation 4*/
		{ { 1,1,0,0 },
		  { 0,1,0,0 },
		  { 0,1,0,0 },
		  { 0,0,0,0 }}

	},

	//Mirrored L
	{

		/*Rotation 1*/
		{ { 1,0,0,0 },
		  { 1,1,1,0 },
		  { 0,0,0,0 },
		  { 0,0,0,0 }},
		/*Rotation 2*/
		{ { 0,1,1,0 },
		  { 0,1,0,0 },
		  { 0,1,0,0 },
		  { 0,0,0,0 }},
		/*Rotation 3*/
		{ { 0,0,0,0 },
		  { 1,1,1,0 },
		  { 0,0,1,0 },
		  { 0,0,0,0 }},
		/*Rotation 4*/
		{ { 0,1,0,0 },
		  { 0,1,0,0 },
		  { 1,1,0,0 },
		  { 0,0,0,0 }}

	}

	};//End of rotations

	//Iterator for stored shapes.
	//I = Piece index
	for(int i = 0; i < 7; ++i) 
	{
		std::unique_ptr<Tetris_Shape> shape = std::make_unique<Tetris_Shape>();
		//r = rotation number
		for(int r = 0; r < 4; ++r) 
		{
			//x = col
			for(int x = 0; x < 4; ++x) 
			{
				//y = row
				for(int y = 0; y < 4; ++y) 
				{
					//Fill the layouts of the shapes
					shape->layouts[r][x][y] = rotations[i][r][x][y];
				}
			}
			shape->change_rotation(0);
		}
		shape->colour = static_cast<Tetris_Shape::Colour>(i + 1);
		shapes.push_back(std::move(shape));
	}
}
