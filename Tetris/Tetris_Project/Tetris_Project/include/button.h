#pragma once
#ifndef __BUTTON_H_
#define __BUTTON_H_

#include <memory>
#include <SDL.h>
#include <string>

enum class Mouse_State
{
	NO_CHANGE,
	MOUSE_OVER,
	MOUSE_DOWN,
	MOUSE_UP,
};

class Graphics;

class Button 
{

public:

	//Default constructor required when using [] operator for maps
	Button() = default;
	Button(Graphics& graphics, const int height, const int width);

	void set_position(const int x, const int y);
	SDL_Point get_position() const;
	void set_texture(std::shared_ptr<SDL_Texture*>& text);

	int height() const { return m_height; };
	int width() const { return m_width; };

	std::string handle_event(SDL_Event* e);

	void draw(const Graphics& graphics);

	std::string id, label;

	int m_width;
	int m_height;

	SDL_Point position;
	SDL_Rect source_rect, desination_rect;
	Mouse_State current_state;
	std::shared_ptr<SDL_Texture*> button_texture;
};


#endif //__BUTTON_H_