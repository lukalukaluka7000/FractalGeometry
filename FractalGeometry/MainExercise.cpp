#define PI 3.141592653589793
#include "MainExercise.h"
#include <glm\gtc\type_ptr.hpp>
#include <vector>
unsigned int VBO;

#define LIMIT 200
#define ODMAK_OD_RUBA 30.0f
int vek_size;
MainExercise::MainExercise() : _windowWidth(200), _windowHeight(200)
{
}

MainExercise::~MainExercise()
{
}

void MainExercise::init(int windowWidth, int windowHeight, int startX, int startY) {
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

	_window.initWindow("Visualizing Mandelbrot", _windowWidth, _windowHeight, 1368, 468, 0x0);
	
	initShaders();
	initStaticData();
	_mandelbrot.init(4.0f, _windowWidth, _windowHeight, LIMIT, glm::vec2(0.0f, 0.0f), ODMAK_OD_RUBA);
	_mandelbrot.prepareOverlapingCoordinatePlanes();
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
	glGenBuffers(1, &VBO);
	//BIND THE BUFFER SO WE CAN UPLOAD
	//we want ths buffer to be active
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	std::vector<unsigned int> pixelData = GeneratePixels(); vek_size = pixelData.size();
	//UPLOAD THE DATA
	glBufferData(GL_ARRAY_BUFFER, pixelData.size() * sizeof(unsigned int), &pixelData[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_UNSIGNED_INT, GL_FALSE, 2 * sizeof(GL_UNSIGNED_INT), (void*)0);
	//unbind the buffer with 0
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void MainExercise::initShaders() {
	_glslProgram.compileShaders("./Shaders/mandelbrot.vert", "./Shaders/mandelbrot.frag");
	_glslProgram.addAttribute("pixel");
	_glslProgram.linkShaders();
}

void MainExercise::exerciseLoop()
{
	while (_gameState != GameState::EXIT ) {

		//process Input

		//mandelbrotProgram.Update

		drawGame();
	}
}
void MainExercise::drawGame()
{
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_glslProgram.use();

	GLushort SWLocation = _glslProgram.getUniformLocation("SW");
	glUniform1f(SWLocation, _windowWidth);
	GLushort SHLocation = _glslProgram.getUniformLocation("SH");
	glUniform1f(SHLocation, _windowHeight);

	GLushort limitLocation = _glslProgram.getUniformLocation("limit");
	glUniform1i(limitLocation, _mandelbrot.getLimit());

	GLushort uvMinLocation = _glslProgram.getUniformLocation("uvMin");
	glUniform2fv(uvMinLocation, 1, glm::value_ptr(_mandelbrot.getUVMin()));
	GLushort uvMaxLocation = _glslProgram.getUniformLocation("uvMax");
	glUniform2fv(uvMaxLocation, 1, glm::value_ptr(_mandelbrot.getUVMax()));

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glDrawArrays(GL_POINTS, 0, vek_size);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	_glslProgram.unuse();
	_window.swapBuffer();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void MainExercise::processInput()
{
}



