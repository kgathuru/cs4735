#include "engine.h"

controller::engine::engine(){
	
}

void controller::engine::keyboard(unsigned char key, int x, int y){
	switch (key){
		case 'w':
			cout << "w pressed"; 
	}
	glutPostRedisplay();
}

bool controller::engine::start(bool finish){

	float t = 0.0;
	float increment = 0.1;
	
	//Just tentative framework code to get this started
	while(!finish)
	{
		//method to move ship
		
		//method to move each asteroid
			
		//Check for collision after each asteroid moves
		

		t = t + increment;
	}

}

bool controller::engine::end(){

}
