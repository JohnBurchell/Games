#include "g_interface.h"
#include <fstream>
#include <algorithm>

G_Interface::G_Interface(Graphics& graphics) :

buttons(0),
type(UI_Type::PLAYING)
{
};

G_Interface::G_Interface() 

{
	SDL_Rect* test_rect;

	test_rect = new SDL_Rect{0,0,0,0};

};

void G_Interface::setup_main_menu(Graphics& graphics)
{
	create_button(graphics, "Play", "Play Game", 75, 200, 100, 200);
	create_button(graphics, "Score", "High Scores", 75, 200, 100, 350);
	create_button(graphics, "Exit", "Exit Game", 75, 200, 100, 500);
	type = UI_Type::MAIN;
}

void G_Interface::setup_pause(Graphics& graphics)
{
	create_button(graphics, "Play", "    Resume", 75, 200, 100, 200);
	create_button(graphics, "Main", "Main Menu", 75, 200, 100, 350);
	create_button(graphics, "Exit", "Exit Game", 75, 200, 100, 500);
	type = UI_Type::PAUSE;
}

void G_Interface::setup_scoreboard(Graphics& graphics)
{
	create_button(graphics, "Main", "Main Menu", 75, 200, 225, 550);
	create_button(graphics, "Exit", "Exit Game", 75, 200, 0, 550);
	type = UI_Type::HIGH_SCORE;
}

void G_Interface::setup_scoring(Graphics& graphics)
{
	create_button(graphics, "Main", "Main Menu", 75, 200, 225, 550);
	create_button(graphics, "Exit", "Exit Game", 75, 200, 0, 550);
	type = UI_Type::SCORING;
}

void G_Interface::create_button(Graphics& graphics, std::string id, std::string label, int height, int width, int pos_x, int pos_y)
{
	Button button{ graphics, height, width };
	button.label = label;
	button.id = id;
	button.set_position(Constants::SCREEN_WIDTH / 2 - pos_x, pos_y);
	buttons.push_back(button);
}

void G_Interface::update(std::map<std::string, std::string>& map)
{
	for (auto& x : map){
		values[x.first] = x.second;
	}
}

void G_Interface::render_ui(Graphics& graphics)
{
	for (auto& x : buttons){
		x.draw(graphics);
	}
	std::vector<Player_Record> players;

	switch (type) {
	case UI_Type::MAIN:
		graphics.draw_text_to_pixel("NATC - Not Another Tetris Clone!", 150, 50);
		graphics.draw_text_to_pixel("Please choose from below:", 180, 100);
		break;
	case UI_Type::PAUSE:
		graphics.draw_text_to_pixel("-PAUSED-", 270, 100);
		break;
	case UI_Type::HIGH_SCORE:
		graphics.draw_text_to_pixel("Rank", 150, 50);
		graphics.draw_text_to_pixel("Name", 250, 50);
		graphics.draw_text_to_pixel("Score", 350, 50);
		graphics.draw_text_to_pixel("Lines", 450, 50);

		players = get_players();

		for (size_t i = 0; i < players.size() && i < 8; ++i){
			graphics.draw_text_to_pixel(std::to_string(i + 1), 170, 50 + (50 * (i + 1)));
			graphics.draw_text_to_pixel(players[i].name, 250, 50 + (50 * (i + 1)));
			graphics.draw_text_to_pixel(players[i].score, 360, 50 + (50 * (i + 1)));
			graphics.draw_text_to_pixel(players[i].lines, 460, 50 + (50 * (i + 1)));
		}

		break;
	case UI_Type::SCORING:
		graphics.draw_text_to_pixel("Game Over!", 250, 50);
		graphics.draw_text_to_pixel("You scored " + values["Score"], 240, 100);
		graphics.draw_text_to_pixel("You completed " + values["Lines"] + " lines ", 190, 150);
		graphics.draw_text_to_pixel("And you reached level " + values["Level"], 190, 200);
		graphics.draw_text_to_pixel(values["Player_Name"], 100, 400);
		graphics.draw_text_to_pixel("Please enter a name for the scoreboard!", 100, 300);
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

	auto compare = [](const Player_Record& a, const Player_Record& b) { return std::stoi(a.score) > std::stoi(b.score); };
	std::sort(names.begin(), names.end(), compare);

	return names;
}

Button::Button(Graphics& graphics, const int height, const int width) :

current_state(Mouse_State::NO_CHANGE),
height(height),
width(width)

{
	position.x = 0;
	position.y = 0;
	source_rect.x = 0;
	source_rect.y = 0;
	source_rect.w = width;
	source_rect.h = height;
	button_texture = graphics.load_image("../../images/buttons_1.bmp", true);
};

Button::Button() :

current_state(Mouse_State::NO_CHANGE),
height(0),
width(0)

{
	position.x = 0;
	position.y = 0;

};

void Button::set_position(const int x, const int y)
{
	position.x = x;
	position.y = y;
}

std::string Button::handle_event(SDL_Event* e)
{
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP){
		int x, y;
		SDL_GetMouseState(&x, &y);

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if (x < position.x)
		{
			inside = false;
		}
		//Mouse is right of the button
		else if (x > position.x + width)
		{
			inside = false;
		}
		//Mouse above the button
		else if (y < position.y)
		{
			inside = false;
		}
		//Mouse below the button
		else if (y > position.y + height)
		{
			inside = false;
		}

		//Mouse is outside button
		if (!inside)
		{
			current_state = Mouse_State::NO_CHANGE;
			source_rect.x = 0;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch (e->type)
			{
			case SDL_MOUSEMOTION:
				current_state = Mouse_State::MOUSE_OVER;
				source_rect.x = 200;
				break;

			case SDL_MOUSEBUTTONDOWN:
				current_state = Mouse_State::MOUSE_DOWN;
				return id;
				break;

			case SDL_MOUSEBUTTONUP:      
				current_state = Mouse_State::MOUSE_UP;
				break;
			}
		}
	}

	return "no_action";
}

//Graphics ref probably needed here.
void Button::draw(Graphics& graphics)
{
	graphics.render_texture(button_texture, position.x, position.y, &source_rect);
	graphics.draw_text_to_pixel(label, position.x + (width / 2) - label.length() - 45, position.y + (height / 2 - 10));
}

