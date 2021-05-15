#define PI 3.141592653589793
#include "MainExercise.h"
#include <glm\gtc\type_ptr.hpp>
#include <vector>
#include <cmath>
#define LIMIT 32
#define ODMAK_OD_RUBA 30.0f

MainExercise::MainExercise() : _windowWidth(200), _windowHeight(200)
{
}

MainExercise::~MainExercise()
{
}

void MainExercise::init(float windowWidth, float windowHeight, int startX, int startY) {
	_windowWidth = windowWidth;
	_windowHeight = windowHeight;
	_startX = startX;
	_startY = startY;
	_gameState = GameState::RUNNING;
}
void MainExercise::run()
{
	initSystems();

	exerciseLoop();
}

void MainExercise::initSystems()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	_window.initWindow("Visualizing Mandelbrot", _windowWidth, _windowHeight, 1368, 468, _window.RESIZABLE /*| _window.BORDERLESS*/);
	
	initShaders();
	initStaticData();
	_mandelbrot.init(4.0f, _windowWidth, _windowHeight, LIMIT, glm::vec2(0.0f, 0.0f), ODMAK_OD_RUBA);
	_mandelbrot.overlapCoordinatePlanes();
	sendUniforms();
}
std::vector<unsigned int> MainExercise::GeneratePixels() {
	std::vector<unsigned int> temp;
	for (int i = 0; i < _windowWidth; i++) {
		for (int j = 0; j < _windowHeight; j++) {
			temp.push_back(i);
			temp.push_back(j);
		}
	}
	return temp;
}
void MainExercise::initStaticData()
{
	glGenBuffers(1, &_VBO);
	//BIND THE BUFFER SO WE CAN UPLOAD
	//we want ths buffer to be active
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);

	std::vector<unsigned int> pixelData = GeneratePixels();
	//UPLOAD THE DATA
	glBufferData(GL_ARRAY_BUFFER, pixelData.size() * sizeof(unsigned int), &pixelData[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_UNSIGNED_INT, GL_FALSE, 2 * sizeof(GL_UNSIGNED_INT), (void*)0);

	//unbind the buffer with 0
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void MainExercise::sendUniforms() {
	_glslProgram.use();
	GLushort SWLocation = _glslProgram.getUniformLocation("SW");
	glUniform1f(SWLocation, _windowWidth);
	GLushort SHLocation = _glslProgram.getUniformLocation("SH");
	glUniform1f(SHLocation, _windowHeight);

	GLushort limitLocation = _glslProgram.getUniformLocation("limit");
	glUniform1i(limitLocation, _mandelbrot.getLimit());

	_glslProgram.unuse();
}
void MainExercise::initShaders() {
	_glslProgram.compileShaders("./Shaders/mandelbrot.vert", "./Shaders/mandelbrot.frag");
	_glslProgram.addAttribute("pixel");
	_glslProgram.linkShaders();
}

void MainExercise::exerciseLoop()
{
	while (_gameState != GameState::EXIT ) {

		processInput();
		
		//std::cout << _mandelbrot.getCenter().x << " " << _mandelbrot.getCenter().y << std::endl;
		_mandelbrot.overlapCoordinatePlanes();
		
		drawGame();
	}
}
void MainExercise::drawGame()
{
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_glslProgram.use();

	GLushort uvMinLocation = _glslProgram.getUniformLocation("uvMin");
	glUniform2fv(uvMinLocation, 1, glm::value_ptr(_mandelbrot.getUVMin()));
	GLushort uvMaxLocation = _glslProgram.getUniformLocation("uvMax");
	glUniform2fv(uvMaxLocation, 1, glm::value_ptr(_mandelbrot.getUVMax()));

	glDrawArrays(GL_POINTS, 0, _windowWidth*_windowHeight);

	_glslProgram.unuse();
	_window.swapBuffer();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void MainExercise::processInput()
{
	SDL_Event evnt;
	
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEWHEEL:
			//update mouse coords only when wheel evnt activates
			//int x, y;
			//SDL_GetMouseState(&x, &y);
			//glm::vec2 oldCenter = _mandelbrot.getCenter();
			//glm::vec2 newCenterDirection = _mandelbrot.convertDisplayToComplexCoords(glm::vec2(float(x), float(y)));
			////(newCenterDirection - oldCenter)
			//glm::vec2 res = (newCenterDirection - oldCenter) ;
			///*if (glm::length(res) > .3f) {
			//	res /= 2.5f;
			//}*/
			//std::cout << oldCenter.x << " " << oldCenter.y << std::endl;
			//std::cout << newCenterDirection.x << " " << newCenterDirection.y << std::endl;
			//std::cout << res.x << " " << res.y << std::endl;
			//std::cout << _mandelbrot.getScrollCounter() << std::endl;
			//_mandelbrot.setCenter(newCenterDirection);
			//std::cout << _mandelbrot.getCenter().x << " " << _mandelbrot.getCenter().y << std::endl;
			if (evnt.wheel.y > 0) {
				// 1.1 constant got on geogebra for less steep function
				//_mandelbrot.setW(4.0f / pow(1.1f, _mandelbrot.getAndIncrementScrollCounter()));
				int zoomLevel = _mandelbrot.getAndIncrementScrollCounter();
				float zoomValue = 0.1f / (pow(1.01, zoomLevel));
				std::cout << _mandelbrot.getStartingW() / pow(1.1, zoomLevel) << std::endl;
				std::cout << _mandelbrot.getW() - zoomValue << std::endl << std::endl;
				float result = _mandelbrot.getStartingW() / pow(1.1, zoomLevel);
				_mandelbrot.setW(result);
			}
			else if (evnt.wheel.y < 0) {
				//_mandelbrot.setW(4.0f / pow(1.1f, _mandelbrot.getAndDecrementScrollCounter()));
				int zoomLevel = _mandelbrot.getAndDecrementScrollCounter();
				float zoomValue = 0.1f / (pow(1.01, zoomLevel));
				float result = _mandelbrot.getStartingW() / pow(1.1, zoomLevel);
				_mandelbrot.setW(result);
			}
			//std::cout << _mandelbrot.getW() << std::endl;
			break;
		case SDL_KEYDOWN:
			_inputManager.keyPressed(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.keyRelease(evnt.key.keysym.sym);
			break;
		}
		
	}
	float increment;
	if (_inputManager.isKeyPressed(SDLK_w))
	{
		//increment = 1.0f / (pow(1.1f, float(_mandelbrot.getScrollCounter())));
		increment = 0.001f / (pow(1.125, _mandelbrot.getScrollCounter()));
		_mandelbrot.setCenter(glm::vec2(_mandelbrot.getCenter().x, _mandelbrot.getCenter().y + increment));
	}
	if (_inputManager.isKeyPressed(SDLK_a))
	{
		//increment = 1.0f / (pow(1.1f, float(_mandelbrot.getScrollCounter())));
		increment = 0.001f / (pow(1.125, _mandelbrot.getScrollCounter()));
		_mandelbrot.setCenter(glm::vec2(_mandelbrot.getCenter().x - increment, _mandelbrot.getCenter().y));
	}
	if (_inputManager.isKeyPressed(SDLK_s))
	{
		/*increment = 1.0f / (pow(1.1f, float(_mandelbrot.getScrollCounter())));*/
		increment = 0.001f / (pow(1.125, _mandelbrot.getScrollCounter()));
		_mandelbrot.setCenter(glm::vec2(_mandelbrot.getCenter().x, _mandelbrot.getCenter().y - increment));
	}
	if (_inputManager.isKeyPressed(SDLK_d))
	{
		/*increment = 1.0f / (pow(1.1f, float(_mandelbrot.getScrollCounter())));*/
		increment = 0.001f / (pow(1.125, _mandelbrot.getScrollCounter()));
		_mandelbrot.setCenter(glm::vec2(_mandelbrot.getCenter().x + increment, _mandelbrot.getCenter().y));
	}

}



