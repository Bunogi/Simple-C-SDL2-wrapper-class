#include <cstdint>
#include <iostream>
#include <string>

#include <SDL2/SDL.h>

#include "sdlclass.hpp"

SDL::SDL(const int windowWidth, const int windowHeight, const std::string& windowName, std::uint32_t windowFlags, std::uint32_t renderFlags) {
	window = nullptr;
	renderer = nullptr;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw SDLException("SDL_Init");
	
	window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, windowFlags);
	if (window == nullptr)
		throw SDLException("SDL_CreateWindow");

	renderer = SDL_CreateRenderer(window, -1, renderFlags);
	if (renderer == nullptr) {
		SDL_DestroyWindow(window);
		throw SDLException("SDL_CreateRenderer");
	}

	SDL_GetWindowSize(window, &width, &height);
	renderClearColour = {0x3F, 0x3F, 0x3F, 0xFF};
	lastTime = thisTime = 0;
}

SDL::~SDL() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

Uint32 SDL::getDeltaTime() {
	thisTime = SDL_GetTicks();
	Uint32 dt = thisTime - lastTime;
	lastTime = thisTime;
	return dt;
}

void SDL::setRenderColour(const SDL_Colour& colour) const {
	if (SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a) < 0) 
		throw SDLException("SDL_SetRenderDrawColor");
}

void SDL::drawRectFill(const SDL_Rect& rect, const SDL_Colour& colour) const {
	setRenderColour(colour);
	if (SDL_RenderFillRect(renderer, &rect) < 0) 
		throw SDLException("SDL_RenderFillRect");
}

void SDL::drawRectOutline(const SDL_Rect& rect, const SDL_Colour& colour) const {
	setRenderColour(colour);
	if (SDL_RenderDrawRect(renderer, &rect) < 0) 
		throw SDLException("SDL_RenderFillRect");
}

void SDL::drawLine(const int x1, const int y1, const int x2, const int y2, const SDL_Colour& colour) const {
	setRenderColour(colour);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void SDL::renderPresent() const {
	SDL_RenderPresent(renderer);
}

void SDL::setRenderClearColour(const SDL_Colour& colour) {
	renderClearColour = colour;
}

void SDL::clearRenderer() const {
	SDL_SetRenderDrawColor(renderer, renderClearColour.r, renderClearColour.g, renderClearColour.b, renderClearColour.a);
	SDL_RenderClear(renderer);
}

void SDLException::printError() {
	std::cerr << "SDL Error: " << what() << ": " << SDL_GetError() << "\n";
}
