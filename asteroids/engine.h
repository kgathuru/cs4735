#ifndef ENGINE_H
#define ENGINE_H

#include <GL/glut.h>

/*! the controller namespace contains the classes necessary for running the game */
namespace controller{

/*! the engine class controls the flow of the game */ 
class engine{
  public:
	static void keyboard(unsigned char key, int x, int y);
	static void update(void);
	void init(int *argc,char**argv);
	bool start(bool finish);
	bool end();
	engine();	
	model::world theWorld;
	viewer::view gameView;
	viewer::camera camera1;
};

engine gameEngine; //global engine
};
#endif
