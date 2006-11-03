#include "game.h"
#include "world.cpp"
#include "view.cpp"
#include "engine.cpp"

#include <GL/glut.h>

namespace controller{
	engine gameEngine;
	view gameView;
};

void displayFunc(){
	controller::gameView.display();
}

void keyboardFunc(){
	controller::gameView.display();
}

main(int argc, char **argv) {
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize (640,480);
	glutCreateWindow ("Asteroids3D");
	glutDisplayFunc (displayFunc);
	//glutMouseFunc(MouseButtons);
	glutKeyboardFunc(keyboardFunc);
	//glutMotionFunc(MouseMotion);
	//glutPassiveMotionFunc(MouseMotion);
	//glutTimerFunc(FRAMETIME,Timer,0);
	glViewport(0, 0, 640, 480);
	glutMainLoop();
	return 0;
}

