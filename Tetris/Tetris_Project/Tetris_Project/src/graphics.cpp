#include "graphics.h"
#include <iostream>
#include "SDL_image.h">

namespace
{
	SDL_Color get_colour(const int colour)
	{
		SDL_Color col;
		switch (colour)
		{
		case 1:
			//Red
			col = { 255, 25, 25, 255 };
			break;
		case 2:
			//Yellow
			col = { 255, 184, 13, 255 };
			break;
		case 3:
			//Green
			col = { 61, 255, 73, 255 };
			break;
		case 4:
			//Blue
			col = { 54, 63, 255, 255 };
			break;
		case 5:
			//Teal
			col = { 64, 167, 255, 255 };
			break;
			//Orange
		case 6:
			col = { 232, 148, 40, 255 };
			break;
			//Purple
		case 7:
			col = { 136, 42, 232, 255 };
			break;
		case 8:
			col = { 255, 255, 255, 120 };
			break;
		default:
			col = { 255, 255, 255, 255 };
			break;
		}

		return col;
	}
}

Graphics::Graphics(const int screen_width, const int screen_height) :
    window{ SDL_CreateWindow("Tetris v2 - SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		screen_width, screen_height, SDL_WINDOW_SHOWN)},
    renderer{ SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED) },
	m_screen_width{ screen_width },
	m_screen_height{ screen_height } 

{
	if (window == nullptr)
	{
		std::cout << "Error creating window! " << SDL_GetError() << std::endl;
	}

	if (renderer == nullptr)
	{
		std::cout << "Error creating renderer! " << SDL_GetError() << std::endl;
	}

	//SDL_ShowCursor(SDL_DISABLE);

	if (TTF_Init() == -1) 
	{
		std::cout << "Unable to initialise TTF! " << TTF_GetError() << std::endl;
	}

	font = TTF_OpenFont(FONT_NAME.c_str(), 16);
	if (font == nullptr)
	{
		std::cout << "Error opening font! " << TTF_GetError() << std::endl;
	}
}

Text_Info Graphics::text_information(const char* text) const
{
	int width = 0;
	int height = 0;

	TTF_SizeText(font, text, &width, &height);

	Text_Info info{ width, height };
	return info;
}

void Graphics::render_texture(SDL_Texture* texture, const SDL_Rect& destination, const SDL_Rect* clip) const
{
	SDL_RenderCopy(renderer, texture, clip, &destination);
}

void Graphics::render_texture(SDL_Texture* texture, const int x, const int y, const int colour, const SDL_Rect* clip) const
{
	SDL_Rect destination_rectangle;
	destination_rectangle.x = x;
	destination_rectangle.y = y;

	if (colour != -1)
	{
		auto result = get_colour(colour);
		SDL_SetTextureColorMod(texture, result.r, result.g, result.b);
	}

	if (clip != nullptr) 
	{
		destination_rectangle.w = clip->w;
		destination_rectangle.h = clip->h;
	}
	else 
	{
		SDL_QueryTexture(texture, nullptr, nullptr, &destination_rectangle.w, &destination_rectangle.h);
	}

	render_texture(texture, destination_rectangle, clip);
}

void Graphics::render_outline(const int rows, const int cols, const int tile_size, const int indent) const
{
	SDL_SetRenderDrawColor(renderer, 110,110,110,10);

	for (int i = 0; i <= rows; ++i) 
	{
		//Horizontal Lines
		SDL_RenderDrawLine(renderer, 
			indent,
			i * tile_size,
			indent + (tile_size * cols),
			i * tile_size);
	}

	for (int i = 0; i <= cols; ++i)
	{
		//Verticle Lines
		SDL_RenderDrawLine(renderer, 
			indent + (i * tile_size),
			0, 
			indent + (i * tile_size),
			indent + (tile_size * (cols + 1)));
	}
}

void Graphics::render_rectanlge(const int pos_x, const int pos_y, const int colour, const int tile_size) const
{
	SDL_Color col;
	switch (colour) 
	{
	case 1:
		//Red
		col = { 255, 25, 25, 255 };
		break;
	case 2:
		//Yellow
		col = { 255, 184, 13, 255 };
		break;
	case 3:
		//Green
		col = { 61, 255, 73, 255 };
		break;
	case 4:
		//Blue
		col = { 54, 63, 255, 255 };
		break;
	case 5:
		//Teal
		col = { 64, 167, 255, 255 };
		break;
		//Orange
	case 6:
		col = { 232, 148, 40, 255 };
		break;
		//Purple
	case 7:
		col = { 136, 42, 232, 255 };
		break;
	case 8:
		col = { 255, 255, 255, 120 };
		break;
	default:
		col = { 255, 255, 255, 255 };
		break;
	}

	SDL_Rect rect = { pos_x, pos_y, tile_size, tile_size };
	SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
	SDL_RenderFillRect(renderer, &rect);
}

void Graphics::render_button(const int pos_x, const int pos_y, const int width, const int height, int colour) const
{

	SDL_Color col;
	switch (colour) 
	{
	case 0:
		//Red
		col = { 147, 147, 147, 255 };
		break;
	case 1:
		//Yellow
		col = { 255, 255, 0, 255 };
		break;
	case 2:
		//Green
		col = { 0, 255, 0, 255 };
		break;
	case 3:
		//Blue
		col = { 20, 20, 220, 255 };
		break;
	case 4:
		//Teal
		col = { 51, 204, 255, 255 };
		break;
	default:
		col = { 255, 255, 255, 255 };
		break;
	}

	SDL_Rect rect{ pos_x, pos_y, width, height };
	SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
	SDL_RenderFillRect(renderer, &rect);
}

void Graphics::renderLine(int originX, int originY, int targetX, int targetY) const
{
	SDL_SetRenderDrawColor(renderer, 200, 200, 110, 32);

	SDL_RenderDrawLine(renderer, originX, originY, targetX, targetY);
}

void Graphics::draw_text(const std::string& text, int pos_x, int pos_y, const int tile_size) const
{
	SDL_Color col{ 255, 255, 255, 255 };

	//Destruction of this surface is taken care of by the graphics class.
	SDL_Surface* output = TTF_RenderText_Solid(font, text.c_str(), col);
	if (output == nullptr || output == NULL) 
	{
		std::cout << "Unable to render text " << SDL_GetError() << "\n";
		std::cout << "Unable to render text " << TTF_GetError() << "\n";
	}
	SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, output);

	if (text_texture == nullptr || text_texture == NULL)
	{
		std::cout << "Unable to load texture " << SDL_GetError() << "\n";
		std::cout << "Unable to render text " << TTF_GetError() << "\n";
	}

	render_texture(text_texture, tile_size * pos_x, tile_size * pos_y);

	SDL_FreeSurface(output);
	SDL_DestroyTexture(text_texture);
}

void Graphics::draw_text_to_pixel(const std::string& text, int pos_x, int pos_y) const
{
	SDL_Color col{ 255, 255, 255, 255 };

	//Destruction of this surface is taken care of by the graphics class.
	SDL_Surface* output = TTF_RenderText_Solid(font, text.c_str(), col);
	if (output == nullptr || output == NULL) 
	{
		std::cout << "Unable to render text " << SDL_GetError() << "\n";
		std::cout << "Unable to render text " << TTF_GetError() << "\n";
	}
	SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, output);

	if (text_texture == nullptr || text_texture == NULL)
	{
		std::cout << "Unable to load texture " << SDL_GetError() << "\n";
		std::cout << "Unable to render text " << TTF_GetError() << "\n";
	}

	render_texture(text_texture, pos_x, pos_y);

	SDL_FreeSurface(output);
	SDL_DestroyTexture(text_texture);
}

std::shared_ptr<SDL_Texture*> Graphics::load_image(const std::string& file_name, bool black_is_transparent)
{
	if (loaded_images.count(file_name) == 0)
	{
		//It needs to be loaded
		SDL_Texture* texture;

		//Loads all (almost) image types
		SDL_Surface* surface = IMG_Load(file_name.c_str());
		if (black_is_transparent)
		{
			//0 = black.
			SDL_SetColorKey(surface, SDL_TRUE, 0);
		}

		if (surface == nullptr)
		{
			//Error loading
			auto error = "Cannot load texture " + file_name + "!";
			throw std::runtime_error(error);
		}
		texture = SDL_CreateTextureFromSurface(renderer, surface);

		if (texture == nullptr)
		{
			//Error loading
			auto error = "Cannot load texture " + file_name + "!";
			throw std::runtime_error(error);
		}

		SDL_FreeSurface(surface);
		loaded_images[file_name] = std::make_shared<SDL_Texture*>(texture);
	}

	return loaded_images[file_name];
}


void Graphics::set_title(const std::string& input) const
{
	SDL_SetWindowTitle(window, input.c_str());
}

void Graphics::update() const
{
	SDL_RenderPresent(renderer);
}

void Graphics::clear() const
{
	SDL_SetRenderDrawColor(renderer, 0,0,0,255);
	SDL_RenderClear(renderer);
}

Graphics::~Graphics()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(font);
	TTF_Quit();
}
