#include "graphics.h"
#include "common.h"

Graphics::Graphics() :

	window{ SDL_CreateWindow("Platformer - 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
							 Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, SDL_WINDOW_SHOWN) },
	renderer{ SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED) }

{
	if (window == NULL){
		std::cout << "Error creating window! " << SDL_GetError() << std::endl;
		throw Window_Error();
	}

	if (renderer == NULL){
		std::cout << "Error creating renderer! " << SDL_GetError() << std::endl;
		throw Renderer_Error();
	}

	SDL_ShowCursor(SDL_DISABLE);
}

SDL_Texture* Graphics::loadImage(const std::string& fileName, bool black_is_transparent)
{
	if (loadedImages.count(fileName) == 0)	{
		SDL_Texture* texture;
		SDL_Surface* surface = SDL_LoadBMP(fileName.c_str());

		if (black_is_transparent) {
			//0 = black, this ignores black around the image
			SDL_SetColorKey(surface, SDL_TRUE, 0);
		}

		if (surface == nullptr) {
			auto error = "Error creating surface for " + fileName + "!" + SDL_GetError();
			throw Surface_Error();
		}
		texture = SDL_CreateTextureFromSurface(renderer, surface);

		if (texture == nullptr) {
			auto error = "Cannot load texture " + fileName + "!" + SDL_GetError();
			throw Texture_Error();
		}

		SDL_FreeSurface(surface);
		loadedImages[fileName] = texture;
	}

	return loadedImages[fileName];
}

void Graphics::renderTexture(SDL_Texture* texture, const int x, const int y, const SDL_Rect* clip) const
{
	SDL_Rect destRectangle;
	destRectangle.x = x;
	destRectangle.y = y;

	if (clip != nullptr) {
		destRectangle.w = clip->w;
		destRectangle.h = clip->h;
	}
	else {
		SDL_QueryTexture(texture, nullptr, nullptr, &destRectangle.w, &destRectangle.h);
	}

	renderTexture(texture, destRectangle, clip);
}

void Graphics::renderTexture(SDL_Texture* texture, const SDL_Rect destination, const SDL_Rect *clip) const
{
	SDL_RenderCopy(renderer, texture, clip, &destination);
}

void Graphics::flip()
{
	SDL_RenderPresent(renderer);
}

void Graphics::clear()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

Graphics::~Graphics()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	for (auto& x : loadedImages)
	{
		SDL_DestroyTexture(x.second);
	}
}


void Graphics::renderLine(float originX, float originY, float targetX, float targetY)
{
	SDL_SetRenderDrawColor(renderer, 200, 200, 110, 32);

	SDL_RenderDrawLine(renderer, originX + 16, originY + 16, targetX + 16, targetY + 16);
}
//Remove later
void Graphics::render_rectanlge(const float pos_x, const float pos_y, const int colour, int width, int height)
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
	SDL_Rect rect = { pos_x, pos_y, width, height };
	SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
	SDL_RenderFillRect(renderer, &rect);
}

void Graphics::update_FPS(const std::string fps)
{
	std::string fps_and_title = "Platformer - Last Frame: " + fps;
	SDL_SetWindowTitle(window, fps_and_title.c_str());
}