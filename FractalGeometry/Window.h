#pragma once
#include<SDL/SDL.h>
#include <string>

class Window
{
public:
	static enum  WindowFlags
	{
		INVISIBLE = 1 << 0,  // binary 0001
		FULLSCREEN = 1 << 1, //// binary 0010
		BORDERLESS = 1 << 2,
		RESIZABLE = 1 << 3
	};
	void initWindow(std::string windowName, int SW, int SH, int startX, int startY, unsigned int flagThatWasPassed);
	void swapBuffer();
	SDL_Window* _sdlWindow;
private:
	int _screenWidth;
	int _screenHeight;
	
};

