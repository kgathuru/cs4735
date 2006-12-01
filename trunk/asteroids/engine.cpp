#include "engine.h"

using controller::gameEngine;

/** constructor for the engine class */
controller::engine::engine(){
	status = GAME_LEVEL1;
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
	if(gameEngine.getStatus() == GAME_LEVEL1)
		gameEngine.theWorld.update();

	if(gameEngine.theWorld.serenity.getPosition().z == 0){
		gameEngine.setStatus(GAME_START);
	} else if (gameEngine.theWorld.serenity.getPosition().z == -WORLD_DEPTH){
		gameEngine.setStatus(GAME_WON);
	} else if (gameEngine.theWorld.serenity.getHealth() < 1) {
		gameEngine.setStatus(GAME_OVER);
	} 

}

/** deals with input from keyboard */
void controller::engine::keyboard(unsigned char key, int x, int y){

	if(gameEngine.getStatus() == GAME_LEVEL1)
	{
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
		case 'q':
			if(gameEngine.getStatus() != GAME_PAUSE)
				gameEngine.setStatus(GAME_PAUSE);
			else
				gameEngine.setStatus(GAME_LEVEL1);
			break;
	}

	glutPostRedisplay();
	}	
	//Only let the player unpause the game, no other movement when paused
	else if(key == 'q')
	{
		gameEngine.setStatus(GAME_LEVEL1);
	}

}

/** deals with special keys */
void controller::engine::keypad(int key, int x, int y){

	if(gameEngine.getStatus() == GAME_LEVEL1)
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
	static int is_quit = 0;
	switch(value){
	case MENU_NEW_GAME:
		//new game
		gameEngine.theWorld.serenity.death();
		break;
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
