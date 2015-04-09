#ifndef GRAPHICS_H_
#define GRAPHICS_H_
#pragma once

#ifdef _WIN32
#include <SDL.h>
#endif

#ifdef __linux__
#include <SDL2/SDL.h>
#endif

#include <unordered_map>

class Graphics
{
	public:
		Graphics();
		~Graphics();


		SDL_Texture* loadImage(const std::string& fileName, bool blackIsTransparent);

		void renderTexture(SDL_Texture* texture, const SDL_Rect destination, const SDL_Rect* clip = nullptr) const;
		void renderTexture(SDL_Texture* texture, const float x, const float y, const SDL_Rect* clip = nullptr) const;
		void update_FPS(const std::string fps);
		
		//REMOVE LATER - Debugging
		void render_rectanlge(const float pos_x, const float pos_y, const int colour, int width = 32, int height = 32);
		void renderLine(float originX, float originY, float targetX, float targetY);

		class Renderer_Error{};
		class Window_Error{};
		class Texture_Error{};
		class Surface_Error{};

		void flip();
		void clear();

	private:
		SDL_Window* window;
		SDL_Renderer* renderer;



		//Unordered map used as I don't care about order, but only want the associativity given by a map structure.
		std::unordered_map<std::string, SDL_Texture*> loadedImages;
};

#endif //GRAPHICS_H_
