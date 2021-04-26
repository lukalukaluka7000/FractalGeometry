#pragma once
#include <FractalGeometry\Window.h>
#include <FractalGeometry\MandelBrotProgram.h>

class MainExercise
{
public:
	MainExercise();
	~MainExercise();

	void init(int windowWidth, int windowHeight, int startX, int startY);
	void run();
	void drawGame();
private:
	void initSystems();

	void exerciseLoop();
	void processInput();

	void reshape(int SW, int SH);


	int getWindHeight() { return _windowHeight; }
	int getWindWidth() { return _windowWidth; }

	Window _window;
	MandelBrotProgram _mandelbrot;

	int _windowWidth;
	int _windowHeight;
	int _startX;
	int _startY;
};