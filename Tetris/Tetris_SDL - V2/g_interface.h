#ifndef G_INTERFACE_H_
#define G_INTERFACE_H_
#pragma once

#include "graphics.h"
#include <map>
#include <string>

class Graphics;

enum class Mouse_State {

	NO_CHANGE,
	MOUSE_OVER,
	MOUSE_DOWN,
	MOUSE_UP,
};

class Button {

public:

	Button();
	Button(Graphics& graphics, int height, int width);

	void set_position(const int x, const int y);

	std::string handle_event(SDL_Event* e);

	void draw(Graphics& graphics);

	std::string id, label;
	void test_draw(Graphics& graphics);

private:

	int width, height;

	SDL_Point position;
	SDL_Rect source_rect, desination_rect;
	Mouse_State current_state;
	SDL_Texture* button_texture;
};

class G_Interface
{
public:

	 G_Interface(Graphics& grpahics);
	 G_Interface();

	 void create_button(Graphics& graphics, std::string label, std::string id, int height, int width, int pos_x, int pos_y);

	void setup_main_menu(Graphics& graphics);
	void setup_pause(Graphics& graphics);
	void setup_scoreboard(Graphics& graphics);
	void setup_scoring(Graphics& graphics);

	void update(std::map<std::string, std::string>& map);

	void render_ui(Graphics& graphics);

	std::string get_action();

	//Holds a ref to graphics.
	std::vector<Button> buttons;
	std::string result;

private:

	enum class UI_Type {
		PLAYING,
		MAIN,
		PAUSE,
		HIGH_SCORE,
		SCORING
	};

	struct Player_Record {
		std::string name;
		std::string score;
		std::string lines;
	};

	UI_Type type;

	std::vector<Player_Record> get_players();
	std::map<std::string, std::string> values;
};

#endif //G_INTERFACE_H_

