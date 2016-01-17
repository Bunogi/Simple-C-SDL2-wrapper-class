# Simple C++ SDL2 wrapper class
This is a very simple C++ wrapper class for SDL2 that I've been using in my projects.

Decided it would be nice to have it as a git repo.

Requires C++11.

If you have a general idea of how SDL2 2D rendering works, it should be relatively simple to use.

To use it, start out with a try block and create an SDL object.

```cpp

try {
	SDL sdlclass(800, 600); //Create an SDL window with a width of 800 and height of 600
	sdlclass.setRenderClearColour({0xFF, 0xFF, 0xFF, 0xFF}); //Clear the screen in white instead of the default grey
	SDL_Rect drawme = {300, 300, 200, 200}; 
	SDL_Colour pink = {0xFF, 0x69, 0xB4};

	while (true) { //Drawing/game loop
		//Handle events like you normally would..
		sdlclass.clearRenderer(); //Clear the screen
		//Update drawing positions, etc
		sdlclass.drawRectFill(drawme, pink); //Draw the rectangle drawme with the colour pink
		sdlclass.renderPresent(); //Update the screen 
	}
	catch (SDLException &ex) { //An SDLException will be thrown if something goes wrong, handle it
		ex.printError(); //Output what went wrong(no need to use SDL_GetError())
	}
}
```
