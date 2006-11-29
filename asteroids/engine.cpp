#include "engine.h"

using controller::gameEngine;

controller::engine::engine(){
	
}

void controller::engine::init(int *argc,char**argv){
	gameView.initView(argc, argv);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keypad);
	glutIdleFunc(update);
	glutSetWindow(2);//should use variable or constant
	addMenus();
	glutSetWindow(1);//should use variable or constant

	gameView.display(); //show initial pic

	//glutKeyboardFunc(keyboardFunc);
	//glutMouseFunc(MouseButtons);
	//glutMotionFunc(MouseMotion);
	//glutPassiveMotionFunc(MouseMotion);
	//glutTimerFunc(FRAMETIME,Timer,0);

	glutMainLoop();
}

void controller::engine::addMenus(){
	int mainMenuID = glutCreateMenu(mainMenu);
	glutAddMenuEntry("New Game", MENU_NEW_GAME);
	glutAddMenuEntry("Quit", MENU_GAME_EXIT);
	glutAttachMenu(GLUT_LEFT_BUTTON);
}

void controller::engine::update(void) {
	gameEngine.theWorld.update();
}

void controller::engine::keyboard(unsigned char key, int x, int y){
	switch (key){
		// slide controls for camera
		case 'F':    gameEngine.camera1.slide(0,0,-5.0); break; // slide camera forward
		case 'F'-64: gameEngine.camera1.slide(0,0, 5.0); break; //slide camera back	
		case 'L':    gameEngine.camera1.slide(-5.0, 0, 0); break; // slide camera left
		case 'L'-64: gameEngine.camera1.slide(5.0, 0, 0); break; //slide camera right
		case 'U':    gameEngine.camera1.slide(0, 5.0, 0); break; // slide camera up
		case 'U'-64: gameEngine.camera1.slide(0, -5.0, 0); break; //slide camera down	
		case 'R':    gameEngine.camera1.roll(1.0); break;  // roll to right
		case 'R'-64: gameEngine.camera1.roll(-1.0); break; // roll to left
		case 'P':    gameEngine.camera1.pitch(1.0); break;  // pitch up
		case 'P'-64: gameEngine.camera1.pitch(-1.0); break; // pitch down
		case 'Y':    gameEngine.camera1.yaw(1.0); break;  // yaw right
		case 'Y'-64: gameEngine.camera1.yaw(-1.0); break; // yaw left

		//game controls
		case 'c': // change camera view
		if (gameEngine.camera1.getView() == DEFAULT_CAM){
			gameEngine.camera1.setView(ONBOARD_CAM);
		} else {
			gameEngine.camera1.setView(DEFAULT_CAM);
		} break; 

		// controls for ship
		//Changes speed only
		case 'a': // accelerate ship
		gameEngine.theWorld.serenity.setSpeed(
			gameEngine.theWorld.serenity.getSpeed() + 1.0
		); break; 
		case 'z': // decellerate ship, only to stopping, not reverse
			if(gameEngine.theWorld.serenity.getSpeed() > 0.0){
				gameEngine.theWorld.serenity.setSpeed(
					gameEngine.theWorld.serenity.getSpeed() - 1.0
				); 
			} break; 

		case ' ': //spacebar, fire projectile 
			if(gameEngine.theWorld.serenity.getReload() == 0)
			{
				gameEngine.theWorld.serenity.fire(); 
				gameEngine.theWorld.serenity.setReload(RELOAD_WAIT);
			}
			break;
		case 27: //escape key, exit game
			glutDestroyWindow(1); // shut down our window 
			exit(0); // exit the program...normal termination.
			break;
	}

	glutPostRedisplay();
}

void controller::engine::keypad(int key, int x, int y){
	switch (key){
		// controls for ship
		case GLUT_KEY_UP: //pitch down
			gameEngine.theWorld.serenity.moveUp(); break;
		case GLUT_KEY_DOWN: //pitch up
			gameEngine.theWorld.serenity.moveDown(); break;
		case GLUT_KEY_LEFT: //yaw left
			//gameEngine.theWorld.serenity.yaw(-1.0); break;
			gameEngine.theWorld.serenity.moveLeft(); break;
		case GLUT_KEY_RIGHT: //yaw right
			//gameEngine.theWorld.serenity.yaw(1.0); break;
			gameEngine.theWorld.serenity.moveRight(); break;
	}
	glutPostRedisplay();
}

void controller::engine::mainMenu(int value){
	static int is_quit = 0;
	switch(value){
	case MENU_NEW_GAME:
		//new game
		break;
	case MENU_GAME_EXIT:
		//quit game
		glutDestroyWindow(1);
		break;	
	}
}

bool controller::engine::start(bool finish){

}

bool controller::engine::end(){

}
