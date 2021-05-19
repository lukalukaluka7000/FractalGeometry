#include "MainExercise.h"
#include <glm\gtc\type_ptr.hpp>
#include <vector>
#include <cmath>
#include <FractalGeometry\ResourceManager.h>

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
	_palette = ResourceManager::getTexture("./Assets/palette.png");
	sendUniforms();
}
std::vector<unsigned int> MainExercise::Vertices() {
	std::vector<unsigned int> temp;
	
	temp.push_back(0); temp.push_back(0);
	temp.push_back(_windowWidth); temp.push_back(0);
	temp.push_back(_windowWidth); temp.push_back(_windowHeight);
	temp.push_back(0); temp.push_back(_windowHeight);
	
	return temp;
}
void MainExercise::initStaticData()
{
	glGenBuffers(1, &_VBO);
	//BIND THE BUFFER SO WE CAN UPLOAD
	//we want ths buffer to be active
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);

	std::vector<unsigned int> vertices = Vertices();
	//UPLOAD THE DATA
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(unsigned int), &vertices[0], GL_STATIC_DRAW);
	//offsset 2
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
	GLushort paletteLocation = _glslProgram.getUniformLocation("palette");
	glUniform1i(paletteLocation, 0);

	_glslProgram.unuse();
}
void MainExercise::initShaders() {
	_glslProgram.compileShaders("./Shaders/mandelbrot.vert", "./Shaders/mandelbrot.frag");
	_glslProgram.addAttribute("screenCoords");
	_glslProgram.linkShaders();
}

void MainExercise::exerciseLoop()
{
	while (_gameState != GameState::EXIT ) {

		processInput();

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
	GLushort limitLocation = _glslProgram.getUniformLocation("limit");
	glUniform1i(limitLocation, _mandelbrot.getLimit());

	glBindTexture(GL_TEXTURE_1D, _palette.id);
	glDrawArrays(GL_QUADS, 0, 4); // 1 quad

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
			if (evnt.wheel.y > 0) {
				// 1.1 constant got on geogebra for less steep function
				int zoomLevel = _mandelbrot.getAndIncrementScrollCounter();
				_mandelbrot.setW( 
					_mandelbrot.ExponentialMultiplicativeInverse(
						_mandelbrot.getStartingW(), 1.1f, zoomLevel
				));
				
				_mandelbrot.setLimit(zoomLevel);
			}
			else if (evnt.wheel.y < 0) {
				int zoomLevel = _mandelbrot.getAndDecrementScrollCounter();
				_mandelbrot.setW( 
					_mandelbrot.ExponentialMultiplicativeInverse(
						_mandelbrot.getStartingW(), 1.1f, zoomLevel
				));

				_mandelbrot.setLimit(zoomLevel);
			}
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
	glm::vec2 center;
	if (_inputManager.isKeyPressed(SDLK_w))
	{
		increment = _mandelbrot.ExponentialMultiplicativeInverse(0.001f, 1.125f);
		center = _mandelbrot.getCenter();
		_mandelbrot.setCenter(glm::vec2(center.x, center.y - increment));
	}
	if (_inputManager.isKeyPressed(SDLK_a))
	{
		increment = _mandelbrot.ExponentialMultiplicativeInverse(0.001f, 1.125f);
		center = _mandelbrot.getCenter();
		_mandelbrot.setCenter(glm::vec2(center.x - increment, center.y));
	}
	if (_inputManager.isKeyPressed(SDLK_s))
	{
		increment = _mandelbrot.ExponentialMultiplicativeInverse(0.001f, 1.125f);
		center = _mandelbrot.getCenter();
		_mandelbrot.setCenter(glm::vec2(center.x, center.y + increment));
	}
	if (_inputManager.isKeyPressed(SDLK_d))
	{
		increment = _mandelbrot.ExponentialMultiplicativeInverse(0.001f, 1.125f);
		center = _mandelbrot.getCenter();
		_mandelbrot.setCenter(glm::vec2(center.x + increment, center.y));
	}

}


