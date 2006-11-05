#include "game.h"
#include "world.cpp"
#include "view.cpp"
#include "engine.cpp"
#include "asteroid.h"
#include <GL/glut.h>

void keyboardFunc(unsigned char key, int x, int y){
	controller::gameEngine.keyboard(key, x, y);
}

main(int argc, char * argv[]) {
	controller::gameEngine.init(&argc, argv);
	//glutKeyboardFunc(keyboardFunc);
	//glutMouseFunc(MouseButtons);
	//glutMotionFunc(MouseMotion);
	//glutPassiveMotionFunc(MouseMotion);
	//glutTimerFunc(FRAMETIME,Timer,0);
	glutMainLoop();
	return 0;
}

