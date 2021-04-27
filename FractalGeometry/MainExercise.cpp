#define PI 3.141592653589793
#include "MainExercise.h"
#include<iostream>
#include<GL/glew.h>

#include<glm/glm.hpp>
#include<vector>
#include<algorithm>
#include<random>

#include<glm/glm.hpp>
#include<glm/gtx/transform.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL\SDL.h>
/// --- GLOBALS ---
float SW, SH;
glm::mat4 viewMat = glm::lookAt(glm::vec3(5.0, 5.0, 5.0), glm::vec3(0.0), glm::vec3(0.0,1.0,0.0));
glm::mat4 projMat = glm::frustum(-1.0f, 1.0f, -1.0f, 1.0f, 0.5f, -0.5f);
/// ---------------

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

	_mandelbrot.init(4.0f, _windowWidth, _windowHeight, 150, glm::vec2(0.0f, 0.0f), 30.0f);
}
//int limit = 150; // limit je 200 dosta za Slika 13.9
////int limit = 16; // julijev
//float umin = 0.0f; float umax = 0.0f;
//float vmin = -0.0f; float vmax = 0.0f;
//
//// klascini mandelbrot center(0,0), w=4
//float centerX = 0.0f;//-0.7454265f; // centat komplexne ravnine X
//float centerY = 0.0f;//0.1130090f; // centat komplexne ravnine Y
//float w = 4.0f; // sirina i visina komplexne ravnine
//int cnt = 1;
//float odmakOdRuba = 30.0f;
void MainExercise::exerciseLoop()
{
	while (/*_gameState != GameState::EXIT*/ true) {

		//process Input

		//mandelbrotProgram.Update

		//drawProgram
	}
}
void MainExercise::processInput()
{
}
void MainExercise::drawGame()
{
}


