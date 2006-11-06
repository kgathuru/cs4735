#include "engine.h"

controller::engine::engine(){
	
}

void controller::engine::init(int *argc,char**argv){
	gameView.initView(argc, argv);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(update);
	
	gameView.display(); //show initial pic

	//glutKeyboardFunc(keyboardFunc);
	//glutMouseFunc(MouseButtons);
	//glutMotionFunc(MouseMotion);
	//glutPassiveMotionFunc(MouseMotion);
	//glutTimerFunc(FRAMETIME,Timer,0);

	glutMainLoop();
}

void controller::engine::update(void) {
	controller::gameEngine.theWorld.update();
}

void controller::engine::keyboard(unsigned char key, int x, int y){
	switch (key){
		// slide controls for camera
		case 'F':    controller::gameEngine.camera1.slide(0,0,-5.0); break; // slide camera forward
		case 'F'-64: controller::gameEngine.camera1.slide(0,0, 5.0); break; //slide camera back	
		case 'L':    controller::gameEngine.camera1.slide(-5.0, 0, 0); break; // slide camera left
		case 'L'-64: controller::gameEngine.camera1.slide(5.0, 0, 0); break; //slide camera right
		case 'U':    controller::gameEngine.camera1.slide(0, 5.0, 0); break; // slide camera up
		case 'U'-64: controller::gameEngine.camera1.slide(0, -5.0, 0); break; //slide camera down	
		case 'R':    controller::gameEngine.camera1.roll(1.0); break;  // roll to right
		case 'R'-64: controller::gameEngine.camera1.roll(-1.0); break; // roll to left
		case 'P':    controller::gameEngine.camera1.pitch(1.0); break;  // pitch up
		case 'P'-64: controller::gameEngine.camera1.pitch(-1.0); break; // pitch down
		case 'Y':    controller::gameEngine.camera1.yaw(1.0); break;  // yaw right
		case 'Y'-64: controller::gameEngine.camera1.yaw(-1.0); break; // yaw left
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
