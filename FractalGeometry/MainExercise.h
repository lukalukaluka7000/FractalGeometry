#pragma once
#include <FractalGeometry\Window.h>
#include <FractalGeometry\MandelBrotProgram.h>
#include <FractalGeometry\GLSLProgram.h>
#include <vector>
#include <FractalGeometry\InputManager.h>
enum class GameState { RUNNING, EXIT };
class MainExercise
{
public:
	MainExercise();
	~MainExercise();

	void init(float windowWidth, float windowHeight, int startX, int startY);
	void run();
	void drawGame();
private:
	void initSystems();

	void initStaticData();

	void sendUniforms();

	void exerciseLoop();
	void processInput();

	void reshape(int SW, int SH);


	int getWindHeight() { return _windowHeight; }
	int getWindWidth() { return _windowWidth; }

	void initShaders();

	std::vector<unsigned int> GeneratePixels();
	glm::vec2 get_mouse_texture_coords(int x, int y);

	Window _window;
	MandelBrotProgram _mandelbrot;

	float _windowWidth;
	float _windowHeight;
	int _startX;
	int _startY;

	GameState _gameState;

	GLSLProgram _glslProgram;

	unsigned int _VBO;

	InputManager _inputManager;
};