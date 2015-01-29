#include "graphics.h"

Graphics::Graphics() :

window{ SDL_CreateWindow("Tetris v2 - SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, SDL_WINDOW_SHOWN)},
renderer{ SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED) }

{
	if (window == NULL){
		std::cout << "Error creating window! " << SDL_GetError() << std::endl;
	}

	if (renderer == NULL){
		std::cout << "Error creating renderer! " << SDL_GetError() << std::endl;
	}

	//SDL_ShowCursor(SDL_DISABLE);

	if (TTF_Init() == -1) {
		std::cout << "Unable to initialise TTF! " << TTF_GetError() << std::endl;
	}

	font = TTF_OpenFont(FONT_NAME.c_str(), 16);
	if (font == NULL){
		std::cout << "Error opening font! " << TTF_GetError() << std::endl;
	}
}

void Graphics::render_texture(SDL_Texture *texture, const SDL_Rect& destination, const SDL_Rect *clip) const
{
	SDL_RenderCopy(renderer, texture, clip, &destination);
}

void Graphics::render_texture(SDL_Texture* texture, const int x, const int y, const SDL_Rect* clip)
{
	SDL_Rect destination_rectangle;
	destination_rectangle.x = x;
	destination_rectangle.y = y;

	if (clip != nullptr) {
		destination_rectangle.w = clip->w;
		destination_rectangle.h = clip->h;
	}
	else {
		SDL_QueryTexture(texture, nullptr, nullptr, &destination_rectangle.w, &destination_rectangle.h);
	}

	render_texture(texture, destination_rectangle, clip);
}

void Graphics::render_outline()
{
	SDL_SetRenderDrawColor(renderer, 110,110,110,10);

	for (int i = 0; i <= Constants::BOARD_ROWS; ++i) {
		//Horizontal Lines
		SDL_RenderDrawLine(renderer, 
			Constants::LEFT_INDENT, 
			Constants::LEFT_INDENT + i * Constants::TILE_SIZE,
			Constants::LEFT_INDENT + Constants::TILE_SIZE * Constants::BOARD_COLS, 
			Constants::LEFT_INDENT + i * Constants::TILE_SIZE);
	}

	for (int i = 0; i <= Constants::BOARD_COLS; ++i){
		//Verticle Lines
		SDL_RenderDrawLine(renderer, 
			Constants::LEFT_INDENT + i * Constants::TILE_SIZE, 
			Constants::TILE_SIZE * 5, 
			Constants::LEFT_INDENT + i * Constants::TILE_SIZE, 
			Constants::SCREEN_HEIGHT);
	}
}

void Graphics::render_rectanlge(const int pos_x, const int pos_y, const int colour)
{
	SDL_Color col;
	switch (colour) {
	case 1:
		//Red
		col = { 255, 0, 0, 255 };
		break;
	case 2:
		//Yellow
		col = { 255, 255, 0, 255 };
		break;
	case 3:
		//Green
		col = { 0, 255, 0, 255 };
		break;
	case 4:
		//Blue
		col = { 20, 20, 220, 255 };
		break;
	case 5:
		//Teal
		col = { 51, 204, 255, 255 };
		break;
		//Orange
	case 6:
		col = { 204, 153, 0, 255 };
		break;
		//Purple
	case 7:
		col = { 255, 0, 255, 255 };
		break;
	case 8:
		col = { 255, 255, 255, 120 };
		break;
	default:
		col = { 255, 255, 255, 255 };
		break;
	}
	SDL_Rect rect = { pos_x, pos_y, Constants::TILE_SIZE, Constants::TILE_SIZE };
	SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
	SDL_RenderFillRect(renderer, &rect);
}

void Graphics::render_button(const int pos_x, const int pos_y, const int width, const int height, int colour)
{

	SDL_Color col;
	switch (colour) {

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

void Graphics::draw_text(std::string text, int pos_x, int pos_y)
{
	SDL_Color col{ 255, 255, 255, 255 };

	//Destruction of this surface is taken care of by the graphics class.
	SDL_Surface* output = TTF_RenderText_Solid(font, text.c_str(), col);
	if (output == nullptr || output == NULL) {
		std::cout << "Unable to render text " << SDL_GetError() << "\n";
		std::cout << "Unable to render text " << TTF_GetError() << "\n";
	}
	SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, output);

	if (text_texture == nullptr || text_texture == NULL){
		std::cout << "Unable to load texture " << SDL_GetError() << "\n";
		std::cout << "Unable to render text " << TTF_GetError() << "\n";
	}

	render_texture(text_texture, Constants::TILE_SIZE * pos_x, Constants::TILE_SIZE * pos_y);

	SDL_FreeSurface(output);
	SDL_DestroyTexture(text_texture);
}

void Graphics::draw_text_to_pixel(std::string text, int pos_x, int pos_y)
{
	SDL_Color col{ 255, 255, 255, 255 };

	//Destruction of this surface is taken care of by the graphics class.
	SDL_Surface* output = TTF_RenderText_Solid(font, text.c_str(), col);
	if (output == nullptr || output == NULL) {
		std::cout << "Unable to render text " << SDL_GetError() << "\n";
		std::cout << "Unable to render text " << TTF_GetError() << "\n";
	}
	SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, output);

	if (text_texture == nullptr || text_texture == NULL){
		std::cout << "Unable to load texture " << SDL_GetError() << "\n";
		std::cout << "Unable to load texture " << TTF_GetError() << "\n";
	}

	render_texture(text_texture, pos_x, pos_y);

	SDL_FreeSurface(output);
	SDL_DestroyTexture(text_texture);
}

SDL_Texture* Graphics::load_image(const std::string& file_name, bool black_is_transparent)
{
	if (loaded_images.count(file_name) == 0)
	{
		//It needs to be loaded
		SDL_Texture* texture;
		SDL_Surface* surface = SDL_LoadBMP(file_name.c_str());
		if (black_is_transparent){
			//0 = black.
			SDL_SetColorKey(surface, SDL_TRUE, 0);
		}

		if (surface == nullptr){
			//Error loading
			auto error = "Cannot load texture " + file_name + "!";
			throw std::runtime_error(error);
		}
		texture = SDL_CreateTextureFromSurface(renderer, surface);

		if (texture == nullptr){
			//Error loading
			auto error = "Cannot load texture " + file_name + "!";
			throw std::runtime_error(error);
		}

		SDL_FreeSurface(surface);
		loaded_images[file_name] = texture;
	}

	return loaded_images[file_name];
}


void Graphics::set_title(std::string input)
{
	SDL_SetWindowTitle(window, input.c_str());
}

void Graphics::flip()
{
	SDL_RenderPresent(renderer);
}

void Graphics::clear()
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
