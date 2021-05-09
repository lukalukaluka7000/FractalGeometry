#include<iostream>
#include"MainExercise.h" 


int main(int argc, char* argv[]) {


	MainExercise mainExercise;
	mainExercise.init(400.0f, 400.0f, 50, 50);
	mainExercise.run();

	return 0;
}
