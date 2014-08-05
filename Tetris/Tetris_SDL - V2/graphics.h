#ifndef GRAPHICS_H_
#define GRAPHICS_H_
#pragma once

#include <SDL_ttf.h>
#include <SDL.h>
#include <map>

#include "common.h"

namespace {
	const std::string FONT_NAME = "fonts/kenpixel.ttf";
}

class Graphics
{

public:
	Graphics();
	~Graphics();

	void flip();
	void clear();

	SDL_Texture* Graphics::load_image(const std::string& file_name, bool black_is_transparent);

	void render_texture(SDL_Texture* texture, const int x, const int y, const SDL_Rect* clip_rect = nullptr);
	void render_texture(SDL_Texture* texture, const SDL_Rect& destination, const SDL_Rect* clip = nullptr) const;
	void render_rectanlge(const int pos_x, const int pos_y, const int colour);
	void render_button(const int pos_x, const int pos_y, const int width, const int height, int colour = 0);
	void render_outline();
		
	void draw_text_to_pixel(std::string text, int pos_x, int pos_y);
	void draw_text(std::string text, int pos_x, int pos_y);
	void set_title(std::string);

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	TTF_Font *font;
	std::map<std::string, SDL_Texture*> loaded_images;

};

#endif //GRAPHICS_H_
