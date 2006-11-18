#include "game.h"

#include "engine.cpp"
#include "world.cpp"
#include "view.cpp"
#include "object.cpp"
#include "ship.cpp"
#include "asteroid.cpp"
#include "math.cpp"





main(int argc, char * argv[]) {
	controller::gameEngine.init(&argc, argv);
	return 0;
}
