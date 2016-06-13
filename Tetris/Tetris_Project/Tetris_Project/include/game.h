#ifndef Game_H
#define Game_H
#pragma once

#include "tetris_shape.h"
#include "g_interface.h"
#include "sound.h"
#include "board.h"
#include <unordered_map>
#include <memory>
#include <SDL.h>
#include <chrono>
#include <string>

class Graphics;

class Game {

	enum class Game_State
	{
		SPLASH,
		MAIN_MENU,
		HIGH_SCORE,
		PLAYING,
		PAUSED,
		OPTIONS,
		FINISHED,
		SCORING
	};

public:

	Game();

private:

	void run();

	using Game_Timer = std::chrono::system_clock::time_point;
	using Clock      = std::chrono::system_clock;

	Game_Timer frame_start, frame_end, fall_timer;
	Game_Timer game_start, game_end, pause_start, pause_end;
	
	uint64_t pause_duration, total_time;

	std::vector<std::unique_ptr<Tetris_Shape>> shapes;

	//Current falling shape.
	Tetris_Shape current_shape, next_shape;

	//Memeber Methods.
	void update();
	void draw(const Graphics& graphics);
	void random_piece();
	void input();

	void test_rotate();

	//Check if a line needs to be removed or not.
	void is_whole_line();
	bool drop_timer();

	std::string calc_time(const uint64_t time_taken);

private:
	int score, level, timer, line_count;
	bool m_new_game;
	bool m_sound_toggled;

	uint64_t time_taken;

	std::unique_ptr<Board> m_board;
	std::unique_ptr<Sound> m_sound;

	void create_shapes(Graphics& graphics);
	void gui(const Graphics& graphics);
	void start_new_game();

	Game_State current_state;
	std::unordered_map<std::string, G_Interface> menus;
	std::string action;
	std::string player_name;

	int m_test_shape[4][4];

	void save_player(const std::string& name);
};

#endif //GAME_H_