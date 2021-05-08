#include "Window.h"
#include<iostream>
#include <GL\glew.h>
void Window::initWindow(std::string windowName, int SW, int SH, int startX, int startY, unsigned int flagThatWasPassed)
{
	_screenWidth = SW;
	_screenHeight = SH;

	Uint32 flags = SDL_WINDOW_OPENGL;
	//enum  WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4, RESIZABLE = 0x16 };

	if (flagThatWasPassed & WindowFlags::INVISIBLE) {
		flags |= SDL_WINDOW_HIDDEN;
	}
	if (flagThatWasPassed & WindowFlags::FULLSCREEN) {
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	if (flagThatWasPassed & WindowFlags::BORDERLESS) {
		flags |= SDL_WINDOW_BORDERLESS;
	}
	if (flagThatWasPassed & WindowFlags::RESIZABLE) {
		flags |= SDL_WINDOW_RESIZABLE;
	}

	_sdlWindow = SDL_CreateWindow(windowName.c_str(), startX, startY, SW, SH, flags);
	if (_sdlWindow == nullptr) {
		std::cout << "SDL Window could not be opened or created!" << std::endl;
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
	if (glContext == nullptr) {
		std::cout << "SDL GL_Context could not be or created!" << std::endl;
	}

	GLenum error = glewInit();
	if (error != GLEW_OK) { // to je nula
		std::cout << "GLEW Init could not be instantiated or created!" << std::endl;
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	std::printf("*** OpenGL Version: %s ***\n", glGetString(GL_VERSION));

	// disabled V-Sync
	//SDL_GL_SetSwapInterval(0);

	glClearColor(0, 0, 1, 1);
}

void Window::swapBuffer()
{
	SDL_GL_SwapWindow(_sdlWindow);
}
