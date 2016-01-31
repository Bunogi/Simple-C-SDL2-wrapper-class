#include <iostream>
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"

#include "sdlclass.hpp"

SDL::SDL(const int windowWidth, const int windowHeight, const std::string& windowName, std::uint32_t windowFlags, std::uint32_t renderFlags) {
	window = nullptr;
	renderer = nullptr;
	#ifdef TTF_SUPPORT
	font = nullptr;
	#endif

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

	#ifdef TTF_SUPPORT
	if (TTF_Init() != 0)
		throw TTFException("TTF_Init");
	#endif
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

#ifdef TTF_SUPPORT
void SDL::loadFont(const std::string& fontFile, const int fontSize) {
	if (font != nullptr) {
		std::cerr << "Warning: One font already loaded! Replacing it..\n";
		TTF_CloseFont(font);
	}

	font = TTF_OpenFont(fontFile.c_str(), fontSize);
	if (font == nullptr)
		throw TTFException("TTF_OpenFont");
}

void SDL::print(const int x, const int y, const std::string& message, const SDL_Colour& colour) const {
	if (font == nullptr) {
		throw TTFException("No font loaded!");
	}
	SDL_Surface *textSurface = TTF_RenderText_Blended(font, message.c_str(), colour);
	if (textSurface == nullptr) 
		throw TTFException("TTF_RenderText_Blended");

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (texture == nullptr)
		throw SDLException("SDL_CreateTextureFromSurface");
	
	SDL_Rect destination = {x, y, 0, 0};
	SDL_QueryTexture(texture, NULL, NULL, &destination.w, &destination.h);
	SDL_RenderCopy(renderer, texture, NULL, &destination);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(texture);
}
#endif
