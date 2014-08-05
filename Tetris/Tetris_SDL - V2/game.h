#ifndef Game_H
#define Game_H
#pragma once

#include "graphics.h"
#include "board.h"
#include "common.h"
#include "sound.h"
#include "tetris_shape.h"
#include "g_interface.h"
#include <map>

class Graphics;
class G_Interface;
class Sound;

class Game {

	enum class Game_State{

		SPLASH,
		MAIN_MENU,
		HIGH_SCORE,
		PLAYING,
		PAUSED,
		FINISHED,
		SCORING
	};

public:

	Game();
	~Game();

private:

	void run();

	using Game_Timer = std::chrono::high_resolution_clock::time_point;
	using Clock = std::chrono::system_clock;

	Game_Timer frame_start, frame_end, fall_timer;
	Game_Timer game_start, game_end, pause_start, pause_end;
	
	uint64_t pause_duration, total_time;

	std::vector<Tetris_Shape*> shapes;

	//Board
	Board board;

	//Current falling shape.
	Tetris_Shape current_shape, next_shape, ghost_shape;

	//Memeber Methods.
	void update();
	void draw(Graphics& graphics);
	void draw_shape(Graphics& graphics);
	void draw_next_shape(Graphics& graphics);
	void random_piece();
	void input();

	void start_new_game();

	void create_shapes();
	void gui(Graphics& graphics);

	//Check if a line needs to be removed or not.
	void is_whole_line();
	bool drop_timer();

	std::string calc_time(uint64_t time_taken);

private:
	int score, level, timer, line_count;
	bool new_game;

	uint64_t time_taken;

	Game_State current_state;
	std::map<std::string, G_Interface> menus;
	std::string action;
	std::string player_name;

	void save_player(std::string name);
};

#endif //GAME_H_