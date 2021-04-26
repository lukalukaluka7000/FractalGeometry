#pragma once
#include<SDL/SDL.h>
#include <string>
enum  WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4, RESIZABLE = 0x8 };
class Window
{
public:
	void initWindow(std::string windowName, int SW, int SH, int startX, int startY, unsigned int flagThatWasPassed);
	void swapBuffer();
private:
	int _screenWidth;
	int _screenHeight;
	SDL_Window* _sdlWindow;
};

