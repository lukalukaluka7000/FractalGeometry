#include<iostream>
#include"MainExercise.h" 


int main(int argc, char* argv[]) {


	MainExercise mainExercise;
	//mainExercise.init(320, 200); // kochova krivulja i pahuljica
	mainExercise.init(600, 600);
	//mainExercise.init(600, 600); // IFS paprati
	

	mainExercise.run(argc, argv);

	return 0;
}
