#ifndef GRAPHICS_H_
#define GRAPHICS_H_
#pragma once

#include <SDL2/SDL.h>
#include <unordered_map>

class Graphics
{
	public:
		Graphics();
		~Graphics();


		SDL_Texture* loadImage(const std::string& fileName, bool blackIsTransparent);

		void renderTexture(SDL_Texture* texture, const SDL_Rect destination, const SDL_Rect* clip = nullptr) const;
		void renderTexture(SDL_Texture* texture, const int x, const int y, const SDL_Rect* clip = nullptr) const;
		
		//REMOVE LATER
		void render_rectanlge(const int pos_x, const int pos_y, const int colour, int width = 32, int height = 32);


		void flip();
		void clear();

	private:
		SDL_Window* window;
		SDL_Renderer* renderer;

		class Renderer_Error{};
		class Window_Error{};
		class Texture_Error{};
		class Surface_Error{};

		//Unordered map used as I don't care about order, but only want the associativity given by a map structure.
		std::unordered_map<std::string, SDL_Texture*> loadedImages;
};

#endif //GRAPHICS_H_
