#include "game.h"
#include "world.cpp"
#include "view.cpp"
#include "engine.cpp"
#include "asteroid.h"
#include <GL/glut.h>

main(int argc, char * argv[]) {
	controller::gameEngine.init(&argc, argv);
	return 0;
}

