#ifndef GRAPHICS_H_
#define GRAPHICS_H_
#pragma once

#include <SDL_ttf.h>
#include <SDL.h>
#include <map>
#include <memory>

namespace 
{
	constexpr char* font_name = "fonts/kenpixel.ttf";
	constexpr int font_size = 16;
}

struct Text_Info
{
	int width;
	int height;
};

class Graphics
{

public:
	Graphics(const int screen_height, const int screen_width);
	~Graphics();

	void update() const;
	void clear() const;

	std::shared_ptr<SDL_Texture*> Graphics::load_image(const std::string& file_name, bool black_is_transparent);

	void render_texture(SDL_Texture* texture, const int x, const int y, const int color = 0, const SDL_Rect* clip_rect = nullptr) const;
	void render_texture(SDL_Texture* texture, const SDL_Rect& destination, const SDL_Rect* clip = nullptr) const;
	void render_rectanlge(const int pos_x, const int pos_y, const int colour, const int tile_size = 32) const;
	void render_button(const int pos_x, const int pos_y, const int width, const int height, int colour = 0) const;
	void render_outline(const int rows, const int cols, const int tile_size, const int indent) const;

	void renderLine(int originX, int originY, int targetX, int targetY) const;

	Text_Info text_information(const char* text) const;
		
	void draw_text_to_pixel(const std::string& text, int pos_x, int pos_y) const;
	void draw_text(const std::string& text, int pos_x, int pos_y, const int tile_size = 32) const;
	void set_title(const std::string& title) const;

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	TTF_Font *font;
	std::map<std::string, std::shared_ptr<SDL_Texture*>> loaded_images;

	//Screen variables
	const int m_screen_width;
	const int m_screen_height;

};

#endif //GRAPHICS_H_
