#include "g_interface.h"
#include "graphics.h"
#include <fstream>
#include <algorithm>

G_Interface::G_Interface(const Graphics& graphics, const int screen_width, const int screen_height) :

m_buttons(0),
m_toggle_buttons(0),
type(UI_Type::PLAYING),
m_screen_width(screen_width),
m_screen_height(screen_height)

{};

void G_Interface::setup_main_menu(Graphics& graphics)
{
	int button_height = 75;
	int button_width = 200;

	create_button(graphics, "Play",  "Play Game",	button_height, button_width, 
		m_screen_width / 2 - (button_width / 2), m_screen_height / 2 - (button_width / 2));
	create_button(graphics, "Score", "High Scores", button_height, button_width, 
		m_screen_width / 2 - (button_width / 2), m_screen_height / 2);
	create_button(graphics, "Exit",  "Exit Game",	button_height, button_width, 
		m_screen_width / 2 - (button_width / 2), m_screen_height / 2 + (button_width / 2));
	type = UI_Type::MAIN;
}

void G_Interface::setup_pause(Graphics& graphics)
{
	int button_height = 75;
	int button_width = 200;
	
	create_button(graphics, "Play", "Resume",     button_height, button_width, 
		m_screen_width / 2 - (button_width / 2), m_screen_height / 2 - (button_width));
	create_button(graphics, "Main", "Main Menu",  button_height, button_width, 
		m_screen_width / 2 - (button_width / 2), m_screen_height / 2 - (button_width / 2));
	create_button(graphics, "Options", "Options", button_height, button_width, 
		m_screen_width / 2 - (button_width / 2), m_screen_height / 2);
	create_button(graphics, "Exit", "Exit Game",  button_height, button_width, 
		m_screen_width / 2 - (button_width / 2), m_screen_height / 2 + (button_width / 2));
	type = UI_Type::PAUSE;
}

void G_Interface::setup_scoreboard(Graphics& graphics)
{
	int button_height = 75;
	int button_width = 200;

	create_button(graphics, "Main", "Main Menu", button_height, button_width, 
		m_screen_width / 2 - button_width, 550);
	create_button(graphics, "Exit", "Exit Game", button_height, button_width, 
		m_screen_width / 2 + 3, 550);
	type = UI_Type::HIGH_SCORE;
}

void G_Interface::setup_options(Graphics& graphics)
{
	int button_height = 75;
	int button_width = 200;

	create_toggle_button(graphics, "Toggle_Sound", " ", 40, 40, m_screen_width / 2 - (button_width / 2), m_screen_height / 2 - (button_width / 2));
	create_button(graphics, "Return", "Return", button_height, button_width, m_screen_width / 2 - (button_width / 2), m_screen_height / 2 + (button_width / 2));
	type = UI_Type::OPTIONS;
}

void G_Interface::setup_scoring(Graphics& graphics)
{
	int button_height = 75;
	int button_width = 200;

	create_button(graphics, "Main", "Main Menu", button_height, button_width, m_screen_width / 2 - button_width, 550);
	create_button(graphics, "Exit", "Exit Game", button_height, button_width, m_screen_width / 2 + 3, 550);
	type = UI_Type::SCORING;
}

void G_Interface::create_button(Graphics& graphics, const std::string& id, const std::string& label, const int height, const int width, const int pos_x, const int pos_y)
{
	Button button{ graphics, height, width };
	button.label = label;
	button.id = id;
	button.set_position(pos_x, pos_y);
	m_buttons.push_back(button);
}

void G_Interface::create_toggle_button(Graphics& graphics, const std::string& id, const std::string& label, const int height, const int width, const int pos_x, const int pos_y)
{
	Toggle_Button button{ graphics, height, width };
	button.label = label;
	button.id = id;
	button.set_position(pos_x, pos_y);
	//Change the texture of this button to be a small button
	auto small_button_texture = graphics.load_image("images/small_button.png", true);
	button.set_texture(small_button_texture);
	m_toggle_buttons.push_back(button);
}

void G_Interface::update(const std::map<std::string, std::string>& map)
{
	for (auto& x : map)
	{
		values[x.first] = x.second;
	}
}

void G_Interface::render_ui(const Graphics& graphics)
{
	for (auto& x : m_buttons)
	{
		x.draw(graphics);
	}
	for (auto& x : m_toggle_buttons)
	{
		x.draw(graphics);
	}
	std::vector<Player_Record> players;
	std::string str = "";
	SDL_Point pos;
	switch (type) 
	{
	case UI_Type::MAIN:
		graphics.draw_text_to_pixel("NATC - Not Another Tetris Clone!", m_screen_width / 2 - (graphics.text_information("NATC - Not Another Tetris Clone!").width / 2), 50);
		graphics.draw_text_to_pixel("Please choose from below:", m_screen_width / 2 - (graphics.text_information("Please choose from below:").width / 2), 100);
		break;
	case UI_Type::PAUSE:
		graphics.draw_text_to_pixel("-PAUSED-", m_screen_width / 2 - (graphics.text_information("-PAUSED-").width / 2), 100);
		break;
	case UI_Type::OPTIONS:
		graphics.draw_text_to_pixel("-PAUSED-", m_screen_width / 2 - (graphics.text_information("-PAUSED-").width / 2), 100);
		//Get the position of the toggle button
		pos = m_toggle_buttons.front().get_position();
		graphics.draw_text_to_pixel("Sound Enabled", pos.x + m_toggle_buttons.front().height() + 20, pos.y + (m_toggle_buttons.front().width() / 2) - (graphics.text_information("Sound Enabled").height / 2));
		break;
	case UI_Type::HIGH_SCORE:
		graphics.draw_text_to_pixel("Rank",  m_screen_width / 2 - (100 + graphics.text_information("Rank").width + (graphics.text_information("Name").width)), 50);
		graphics.draw_text_to_pixel("Name",  m_screen_width / 2 - (50 + graphics.text_information("Name").width), 50);
		graphics.draw_text_to_pixel("Score", m_screen_width / 2 + (graphics.text_information("Score").width / 2), 50);
		graphics.draw_text_to_pixel("Lines", m_screen_width / 2 + (50 + graphics.text_information("Rank").width + (graphics.text_information("Lines").width)), 50);

		players = get_players();

		for (size_t i = 0; i < players.size() && i < 8; ++i)
		{
			graphics.draw_text_to_pixel(std::to_string(i + 1), m_screen_width / 2 - (100 + graphics.text_information("Rank").width + (graphics.text_information("Name").width)), 50 + (50 * (i + 1)));
			graphics.draw_text_to_pixel(players[i].name, m_screen_width / 2 - (50 + graphics.text_information("Name").width), 50 + (50 * (i + 1)));
			graphics.draw_text_to_pixel(players[i].score, m_screen_width / 2 + (graphics.text_information("Score").width / 2), 50 + (50 * (i + 1)));
			graphics.draw_text_to_pixel(players[i].lines, m_screen_width / 2 + (50 + graphics.text_information("Rank").width + (graphics.text_information("Lines").width)), 50 + (50 * (i + 1)));
		}

		break;
	case UI_Type::SCORING:
		graphics.draw_text_to_pixel("Game Over!", m_screen_width / 2 - graphics.text_information("Game Over!").width / 2, 50);
		str = "You scored " + values["Score"];
		graphics.draw_text_to_pixel("You scored " + values["Score"], m_screen_width / 2 - graphics.text_information(str.c_str()).width / 2, 100);
		str = "You completed " + values["Lines"] + " lines ";
		graphics.draw_text_to_pixel("You completed " + values["Lines"] + " lines ", m_screen_width / 2 - graphics.text_information(str.c_str()).width / 2, 150);
		str = "And you reached level " + values["Level"];
		graphics.draw_text_to_pixel("And you reached level " + values["Level"], m_screen_width / 2 - graphics.text_information(str.c_str()).width / 2, 200);
		graphics.draw_text_to_pixel(values["Player_Name"], m_screen_width / 2 - graphics.text_information(values["Player_Name"].c_str()).width / 2, 400);
		graphics.draw_text_to_pixel("Please enter a name for the scoreboard!", m_screen_width / 2 - graphics.text_information("Please enter a name for the scoreboard!").width / 2, 300);
		break;
	case UI_Type::PLAYING:
		graphics.draw_text("Next Shape", 16, 4);
		graphics.draw_text("Time : ", 1, 5);
		graphics.draw_text(values["Time_Taken"], 1, 6);
		graphics.draw_text("Score :", 1, 7);
		graphics.draw_text(values["Score"], 1, 8);
		graphics.draw_text("Lines :", 1, 9);
		graphics.draw_text(values["Lines"], 1, 10);
		break;
	default:
		break;
	}
}

std::vector<G_Interface::Player_Record> G_Interface::get_players()
{
	std::ifstream file;
	std::vector<Player_Record> names;
	std::string name;
	file.open("players.dat", std::ios::in);

	while (getline(file, name)){

		std::size_t first_comma = 0, second_comma = 0, end = 0;
		std::string p_name, p_score, p_lines;
		Player_Record player;

		first_comma = name.find(',');
		second_comma = name.find('-');
		end = name.find(";");

		p_name = name.substr(0, std::min(static_cast<int>(first_comma), 5));
		p_score = name.substr(first_comma + 1, end - second_comma);
		p_lines = name.substr(second_comma + 1, (end-1) - second_comma);

		player.name = p_name;
		player.score = p_score;
		player.lines = p_lines;

		names.push_back(player);
	}

	file.close();

	auto compare = [](Player_Record& a, Player_Record& b) { return std::stoi(a.score) > std::stoi(b.score); };
	std::sort(names.begin(), names.end(), compare);

	return names;
}




