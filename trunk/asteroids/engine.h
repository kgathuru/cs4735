#ifndef ENGINE_H
#define ENGINE_H

#include <GL/glut.h>

/** the controller namespace contains the classes necessary for running the game */

namespace controller{

/** the engine class controls the flow of the game */ 

class engine{
	public:
	bool start();
	bool end();
	engine();	
	private:
	//model::world world;
};
//extern engine gameengine;
//extern view gameview;
};
#endif
