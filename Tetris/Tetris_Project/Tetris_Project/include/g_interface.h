#pragma once
#ifndef __G_INTERFACE_H_
#define __G_INTERFACE_H_

#include <map>
#include <string>
#include <memory>
#include <vector>
#include <SDL.h>
#include "button.h"
#include "toggle_Button.h"

class Graphics;

class G_Interface
{
public:

	//Default constructor required when using [] operator for maps
	G_Interface() = default;
	G_Interface(const Graphics& grpahics, const int screen_width, const int screen_height);

	void G_Interface::create_button(Graphics& graphics, const std::string& label, const std::string& id, const int height, const int width, const int pos_x, const int pos_y);
	void G_Interface::create_toggle_button(Graphics& graphics, const std::string& label, const std::string& id, const int height, const int width, const int pos_x, const int pos_y);

	void setup_main_menu(Graphics& graphics);
	void setup_pause(Graphics& graphics);
	void setup_scoreboard(Graphics& graphics);
	void setup_scoring(Graphics& graphics);
	void setup_options(Graphics& graphics);

	void update(const std::map<std::string, std::string>& map);

	void render_ui(const Graphics& graphics);

	const std::string& get_action() const;

	std::vector<Button> m_buttons;
	std::vector<Toggle_Button> m_toggle_buttons;
	std::string result;

private:

	enum class UI_Type 
	{
		PLAYING,
		MAIN,
		PAUSE,
		HIGH_SCORE,
		OPTIONS,
		SCORING
	};

	struct Player_Record 
	{
		std::string name;
		std::string score;
		std::string lines;
	};

	UI_Type type;

	int m_screen_width;
	int m_screen_height;

	std::vector<Player_Record> get_players();
	std::map<std::string, std::string> values;
};

#endif //__G_INTERFACE_H_

