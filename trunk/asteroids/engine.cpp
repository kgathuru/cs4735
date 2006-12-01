#include "engine.h"

using controller::gameEngine;

/** constructor for the engine class */
controller::engine::engine(){
	status = GAME_START;
	pause = true;
}

/** initialises the game 
    \param int argc takes number of arguments 
    \param char** argv takes array of arguments */
void controller::engine::init(int *argc,char**argv){
	gameView.initView(argc, argv);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keypad);
	glutIdleFunc(update);
	addMenus();
	gameView.display(); //show initial pic

	//glutKeyboardFunc(keyboardFunc);
	//glutMouseFunc(MouseButtons);
	//glutMotionFunc(MouseMotion);
	//glutPassiveMotionFunc(MouseMotion);
	//glutTimerFunc(FRAMETIME,Timer,0);

	glutMainLoop();
}

/** adds menus to the display */
void controller::engine::addMenus(){
	int mainMenuID = glutCreateMenu(mainMenu);
	glutAddMenuEntry("New Game", MENU_NEW_GAME);
	glutAddMenuEntry("Quit", MENU_GAME_EXIT);
	glutAttachMenu(GLUT_LEFT_BUTTON);
}

/** updates the game at regular intervals */
void controller::engine::update(void) {
	if (gameEngine.pause) {
		return;
	} else if (gameEngine.theWorld.serenity.getPosition().z == -WORLD_DEPTH){
		gameEngine.setStatus(GAME_WON);
	} else if (gameEngine.theWorld.serenity.getHealth() < 1) {
		gameEngine.setStatus(GAME_OVER);
	} else { 
		gameEngine.theWorld.update(); 
	}

				//give a background for border
	//glColor3f(0.0, 0.0, 0.0);
	//glBegin(GL_QUADS);
	//glVertex3f(-100, -200, 0);
	//glVertex3f(-100, 100, 0);
	//glVertex3f(120, 100, 0);
	//glVertex3f(120, -200, 0);
	//glEnd();

}

/** deals with input from keyboard */
void controller::engine::keyboard(unsigned char key, int x, int y){
//<<<<<<< .mine
	//if  (gameEngine.getStatus() == GAME_START){
	//	//during pause, only allow unpause
	//	if(key == 13){	
	//		gameEngine.pause = false;
	//		gameEngine.setStatus(GAME_LEVEL1);
	//	}
	//	return;
	//}

	//during pause, only allow unpause
	if  (gameEngine.pause){
		if(key == 13){	
			gameEngine.pause = false;
		}
		return;
	}

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
		case 13: //enter key, pause
			if(gameEngine.getStatus() == GAME_LEVEL1) {
				gameEngine.pause = true; 
			} else {
				gameEngine.setStatus(GAME_LEVEL1);
			}	
			break;
	} //switch key
	glutPostRedisplay();
}

/** deals with special keys */
void controller::engine::keypad(int key, int x, int y){

	if(!gameEngine.pause)
	{
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
}

/** deals with selections on the main menu */
void controller::engine::mainMenu(int value){
	switch(value){
	case MENU_NEW_GAME:
		{
		//new game
		model::world newWorld;
		gameEngine.theWorld = newWorld;
		break;
		}	
	case MENU_GAME_EXIT:
		//quit game
		glutDestroyWindow(1);
		break;	
	}
}

/** game status modifier */
void controller::engine::setStatus(GameStatus gameStatus){
	status = gameStatus;
}

/** game status accessor */
GameStatus controller::engine::getStatus(){
	return status;
}
