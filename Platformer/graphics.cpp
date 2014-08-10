#include "graphics.h"
#include "common.h"

Graphics::Graphics() :

window{ SDL_CreateWindow("Platformer - 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
						 Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, SDL_WINDOW_SHOWN) },
renderer{ SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED) }

{
	if (window == NULL){
		std::cout << "Error creating window! " << SDL_GetError() << std::endl;
	}

	if (renderer == NULL){
		std::cout << "Error creating renderer! " << SDL_GetError() << std::endl;
	}

	//TODO - Debug mode to show cursor?
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

void Graphics::testRender(SDL_Texture* texture, int x, int y, int width, int height, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = { x, y, width, height };

	if (clip != nullptr){
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//render to the screen, hopefuly!
	SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
}

//void Graphics::renderToCamera(int x, int y, SDL_Rect* clip, SDL_Point* center, SDL_RendererFlip flip)
//{
//	SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
//}

void Graphics::flip()
{
	SDL_RenderPresent(renderer);
}

void Graphics::clear()
{
	SDL_RenderClear(renderer);
}

Graphics::~Graphics()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}
