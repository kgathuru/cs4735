#include "engine.h"

controller::engine::engine(){
	
}

void controller::engine::init(int *argc,char**argv){
	gameView.initView(argc, argv);
	glutKeyboardFunc(keyboard);
	gameView.display();

	//glutKeyboardFunc(keyboardFunc);
	//glutMouseFunc(MouseButtons);
	//glutMotionFunc(MouseMotion);
	//glutPassiveMotionFunc(MouseMotion);
	//glutTimerFunc(FRAMETIME,Timer,0);

	glutMainLoop();
}

void controller::engine::keyboard(unsigned char key, int x, int y){
	switch (key){
		// slide controls for camera
		case 'w':    cout << "w was pressed"; break;
		case 'F':    camera1.slide(0,0,-1.0); break; // slide camera forward
		case 'F'-64: camera1.slide(0,0, 1.0); break; //slide camera back	
		case 'L':    camera1.slide(-1.0, 0, 0); break; // slide camera left
		case 'L'-64: camera1.slide(1.0, 0, 0); break; //slide camera right
		case 'U':    camera1.slide(0, 1.0, 0); break; // slide camera up
		case 'U'-64: camera1.slide(0, -1.0, 0); break; //slide camera down	
		case 'R':    camera1.roll(1.0); break;  // roll to right
		case 'R'-64: camera1.roll(-1.0); break; // roll to left
		case 'P':    camera1.pitch(1.0); break;  // pitch up
		case 'P'-64: camera1.pitch(-1.0); break; // pitch down
		case 'Y':    camera1.yaw(1.0); break;  // yaw right
		case 'Y'-64: camera1.yaw(-1.0); break; // yaw left
		// angular motion of the camera
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
