#ifndef ENGINE_H
#define ENGINE_H

#include <GL/glut.h>
#include "world.h"
#include "view.h"

using namespace math;

/** the controller namespace contains the classes necessary for running the game */
namespace controller{

/** the engine class controls the flow of the game */
class engine{
  public:
	static void keyboard(unsigned char key, int x, int y);
	static void keypad(int key, int x, int y);
	static void redrawOverlay();
	static void update(void);
	static void mainMenu(int value);
	void addMenus();
	void init(int *argc, char**argv);
	void setStatus(GameStatus gameStatus);
	GameStatus getStatus();
	engine();	
	bool pause; ///< set this to true to pause the game
	viewer::view gameView; ///< the viewer to control display
	model::world theWorld; ///< world objct contains all objects
	viewer::camera camera1; ///< main camera 
  private:
	/** this contains the menu constants */
	enum { MENU_NEW_GAME, MENU_GAME_EXIT };
	GameStatus status;
};

engine gameEngine; ///< global game engine object
};

#endif
