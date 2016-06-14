#include "game.h"
#include "graphics.h"
#include <sstream>
#include <ctime>
#include <fstream>
#include <memory>
#include <iostream>

using namespace std::chrono;

namespace
{
	constexpr float fps = 60.0f;
	constexpr float max_time = 5.0f * 1000 / fps;
	constexpr int board_rows = 16;
	constexpr int board_cols = 10;
	constexpr int tile_size = 32;
	constexpr int screen_height = (board_rows + 5) * tile_size;
	constexpr int screen_width = (board_cols + 10) * tile_size;
}

Game::Game() :
	score(0),
	level(1),
	line_count(0),
	pause_duration(0),
	total_time(0),
	player_name(" "),
	current_state(Game_State::MAIN_MENU),
	current_shape(0, 0),
	next_shape(0, 0),
	m_board(nullptr),
	m_new_game(true),
	m_sound_toggled(true)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	run();
}

void Game::start_new_game()
{
	m_board->new_game();
	random_piece();
	current_shape = next_shape;
	random_piece();
	pause_duration = 0;
	line_count = 0;
	score = 0;
	timer = 0;
	level = 0;
	time_taken = 0;
	game_start = system_clock::now();
	//Cannot send an empty string to the UI when collecting the player name.
	player_name = " ";
	m_new_game = true;
}


void Game::run()
{
	Graphics graphics{ screen_height, screen_width };
	m_board.reset(new Board(graphics, board_cols, board_rows, tile_size));
	m_sound.reset(new Sound());
	m_sound->init_sounds();

	create_shapes(graphics);

	G_Interface main_menu (graphics, screen_width, screen_height);
	main_menu.setup_main_menu(graphics);
	menus.emplace("Main", main_menu);

	G_Interface pause_menu(graphics, screen_width, screen_height);
	pause_menu.setup_pause(graphics);
	menus.emplace("Pause", pause_menu);

	G_Interface scoreboard(graphics, screen_width, screen_height);
	scoreboard.setup_scoreboard(graphics);
	menus.emplace("High_Score", scoreboard);

	G_Interface options(graphics, screen_width, screen_height);
	options.setup_options(graphics);
	menus.emplace("Options", options);

	G_Interface scoring_screen(graphics, screen_width, screen_height);
	scoring_screen.setup_scoring(graphics);
	menus.emplace("Score", scoring_screen);

	G_Interface play_screen(graphics, screen_width, screen_height);
	menus.emplace("Play_Screen", play_screen);

	float previous_frame = 0.0f;

	bool playing = true;

	current_state = Game_State::MAIN_MENU;

	while (playing) 
	{

		frame_start = Clock::now();

		if (m_new_game)
		{
			start_new_game();
		}

		//Get start time.
		const Uint32 start_time = SDL_GetTicks();

		std::string player_name;

		switch (current_state)
		{
		case Game_State::MAIN_MENU:
			m_sound->stop_music();
			break;

		case Game_State::PLAYING:
			//Get start time.
			if (m_new_game) 
			{
				//Start of a new game
				m_sound->play_music();
				game_start = std::chrono::system_clock::now();
				m_new_game = false;
			}
			else if (Mix_PausedMusic())
			{
				pause_end = Clock::now();
				pause_duration += duration_cast<seconds>(pause_end - pause_start).count();
				m_sound->unpause_music();
			}
			//If the current shape is empty, it means there's nothing active.
			if (!m_board->falling_shape) 
			{
				current_shape = next_shape;
				m_board->falling_shape = true;
				random_piece();

				//Reset start time of new shape.
				fall_timer = Clock::now();
			}

			if (m_board->game_over)
			{
				current_state = Game_State::SCORING;
			}

			total_time = static_cast<int>(duration_cast<seconds>(Clock::now() - game_start).count() - pause_duration);
			pause_start = Clock::now();
			break;

		case Game_State::PAUSED:
			m_sound->pause_music();
			break;
		case Game_State::SCORING:
			m_sound->stop_music();
			break;
		case Game_State::HIGH_SCORE:
			break;
		case Game_State::OPTIONS:
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

void Game::draw(const Graphics& graphics)
{
	graphics.clear();
	if (current_state == Game_State::PLAYING || current_state == Game_State::PAUSED) 
	{
		current_shape.draw_current(graphics);
		next_shape.draw_next(graphics);
		m_board->draw(graphics);
	}
	gui(graphics);
	//graphics.renderLine(screen_width / 2, 0, screen_width / 2, screen_height);
	//graphics.renderLine(0, screen_height / 2, screen_width, screen_height / 2);
	graphics.update();
}

/*
	Drops pieces of alloted time has passed and checks for whole lines.
*/

void Game::update() 
{
	//If enough time has passed, drop blocks.
	if(current_state == Game_State::PLAYING && drop_timer())
	{
		m_board->drop_pieces(current_shape, false);
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
			bool result = false;
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
					result = m_board->move_left(current_shape);
					if (!result)
					{
						m_sound->play_sound("Wall_Hit");
					}
					break;
				case SDLK_RIGHT:
					result = m_board->move_right(current_shape);
					if (!result)
					{
						m_sound->play_sound("Wall_Hit");
					}
					break;
				case SDLK_UP:
					m_board->rotate_piece(current_shape);
					break;
				case SDLK_DOWN:
					m_board->drop_pieces(current_shape, false);
					break;
				case SDLK_SPACE:
					m_board->drop_pieces(current_shape, true);
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
			for (auto& x : menus["Pause"].m_buttons)
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
						m_new_game = true;
						current_state = Game_State::MAIN_MENU;
					}
					else if (result == "Exit")
					{
						current_state = Game_State::FINISHED;
					}
					if (result == "Options")
					{
						current_state = Game_State::OPTIONS;
					}
				}
			}
		}

		else if (current_state == Game_State::MAIN_MENU)
		{
			for (auto& x : menus["Main"].m_buttons)
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
			for (auto& x : menus["High_Score"].m_buttons)
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

		else if (current_state == Game_State::OPTIONS)
		{
			for (auto& x : menus["Options"].m_buttons)
			{
				std::string result = x.handle_event(&event);
				if (result != "no_action")
				{

					if (result == "Return")
					{
						current_state = Game_State::PAUSED;
					}
				}
			}

			for (auto& x : menus["Options"].m_toggle_buttons)
			{
				std::string result = x.handle_event(&event);
				if (result == "Toggle_Sound")
				{
					if (x.toggled())
					{
						m_sound->change_sound_level(MIX_MAX_VOLUME);
					}
					else
					{
						m_sound->change_sound_level(0);
					}

					x.toggle_button();
				}
			}
		}

		else if (current_state == Game_State::SCORING) 
		{
			for (auto& x : menus["Score"].m_buttons)
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
	next_shape.x(board_cols / 2 - 1);
	next_shape.y(-3);
}

/*
	Checks if the line is full, i.e. the sum of the whole line is 
	equal to a certain number. For now, that number is 12.
*/
void Game::is_whole_line()
{
	//Sum for calculating a whole line.
	int sum;
	bool line_completed = false;

	for (int i = 0; i < board_rows; ++i) 
	{
		sum = 0;
		for (int j = 0; j < board_cols; ++j) 
		
		{
			if(m_board->board[i][j] > 0) 
			{
				sum++;
			}
		}

		if(sum == board_cols)
		{
			//Line completed
			line_completed = true;

			m_board->clear_line(i);
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

	if (line_completed)
	{
		m_sound->play_sound("Line_Complete");
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

void Game::gui(const Graphics& graphics)
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

		if (current_state == Game_State::OPTIONS)
		{
			menus["Options"].render_ui(graphics);
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


//An alternative is to have one layout for each shape. Each shape would have
//a point of rotation which is used to re-align the origin of the rotation
//this would mean less memory being used to store the rotations, but would
//probably be slower than pre-computing the rotations.
void Game::create_shapes(Graphics& graphics) {

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

	//I = Piece index
	for(int i = 0; i < 7; ++i) 
	{
		std::unique_ptr<Tetris_Shape> shape = std::make_unique<Tetris_Shape>(0, 0);
		shape->set_texture(graphics);
		//r = rotation number
		for(int rot = 0; rot < 4; ++rot)
		{
			//x = col
			for(int col = 0; col < 4; ++col) 
			{
				//y = row
				for(int row = 0; row < 4; ++row) 
				{
					//Fill the layouts of the shapes
					shape->m_layouts[rot][col][row] = rotations[i][rot][col][row];
				}
			}
			shape->change_rotation(0);
		}
		shape->colour(static_cast<Tetris_Shape::Colour>(i + 1));
		shapes.push_back(std::move(shape));
	}
}
