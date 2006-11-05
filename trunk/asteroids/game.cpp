#include "game.h"
#include "world.cpp"
#include "view.cpp"
#include "engine.cpp"
#include "asteroid.h"

#include <GL/glut.h>

namespace controller{
	engine gameEngine;
	view gameView;
};


void keyboardFunc(unsigned char key, int x, int y){
	controller::gameEngine.keyboard(key, x, y);
}

main(int argc, char * argv[]) {
	controller::gameView.init(&argc, argv);
	glutKeyboardFunc(keyboardFunc);
	//glutMouseFunc(MouseButtons);
	//glutMotionFunc(MouseMotion);
	//glutPassiveMotionFunc(MouseMotion);
	//glutTimerFunc(FRAMETIME,Timer,0);
	glViewport(0, 0, 640, 480);
	glutMainLoop();
	return 0;
}

