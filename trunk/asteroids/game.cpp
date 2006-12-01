#include "game.h"

#include "engine.cpp"
#include "world.cpp"
#include "view.cpp"
#include "object.cpp"
#include "ship.cpp"
#include "asteroid.cpp"
#include "projectile.cpp"
#include "math.cpp"

/** takes control and passed to main engine initializer along with parameters
    \param int argc number of arguments 
    \param char** argv array of arguments 
*/
main(int argc, char * argv[]) {
	controller::gameEngine.init(&argc, argv);
	return 0;
}
