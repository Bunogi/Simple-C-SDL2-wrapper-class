#ifndef SDLCLASS_HPP
#define SDLCLASS_HPP

#include <stdexcept>
#include <cstdint>
#include <string>

#include <SDL2/SDL.h>

class SDL {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Colour renderClearColour;
	int width;
	int height;
	public:
		SDL(const int windowWidth, const int windowHeight, const std::string& windowName="Window", std::uint32_t windowFlags=SDL_WINDOW_SHOWN, std::uint32_t renderFlags=SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		~SDL();
		void drawRectFill(const SDL_Rect& rect, const SDL_Colour& colour = {0xFF, 0xFF, 0xFF, 0xFF}) const;
		void drawRectOutline(const SDL_Rect& rect, const SDL_Colour& colour = {0xFF, 0xFF, 0xFF, 0xFF}) const;
		void renderPresent() const;
		void clearRenderer() const;
		void setRenderClearColour(const SDL_Colour& colour);
		int getWidth() {
			return width;
		}
		int getHeight() {
			return height;
		}
};

class SDLException : public std::runtime_error {
	using std::runtime_error::runtime_error;
	public:
		virtual void printError();
};

#endif
