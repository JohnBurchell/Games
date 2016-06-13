#include "button.h"
#include "graphics.h"

Button::Button(Graphics& graphics, int height, int width) :

	current_state(Mouse_State::NO_CHANGE),
	m_height(height),
	m_width(width)

{
	position.x = 0;
	position.y = 0;
	source_rect.x = 0;
	source_rect.y = 0;
	source_rect.w = width;
	source_rect.h = height;
	button_texture = graphics.load_image("images/buttons_1.bmp", true);
};

void Button::set_position(const int x, const int y)
{
	position.x = x;
	position.y = y;
}

SDL_Point Button::get_position() const
{
	return position;
}

std::string Button::handle_event(SDL_Event* e)
{
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
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
		else if (x > position.x + m_width)
		{
			inside = false;
		}
		//Mouse above the button
		else if (y < position.y)
		{
			inside = false;
		}
		//Mouse below the button
		else if (y > position.y + m_height)
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
				source_rect.x = m_width;
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

void Button::set_texture(std::shared_ptr<SDL_Texture*>& tex)
{
	//Replace the previous shared_ptr
	button_texture = tex;
}

//Graphics ref probably needed here.
void Button::draw(const Graphics& graphics)
{
	graphics.render_texture(*button_texture, position.x, position.y, -1, &source_rect);
	graphics.draw_text_to_pixel(label, position.x + (m_width / 2) - (graphics.text_information(label.c_str()).width / 2), position.y + (m_height / 2) - 10);
}