#pragma once

class MainExercise
{
public:
	void run(int argc, char* argv[]);
	void init(int windowWidth, int windowHeight);

	//void renderScene();
	static void display();
	static void reshape(int width, int height);
	static void OnMouseClick(int button, int state, int x, int y);
	static void OnKeyboardClick(unsigned char key, int x, int y);

	int getWindHeight() { return _windowHeight; }
	int getWindWidth() { return _windowWidth; }

private:
	int _windowWidth;
	int _windowHeight;

};