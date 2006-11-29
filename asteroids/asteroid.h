#ifndef ASTEROID_H
#define ASTEROID_H

#include "object.h"
#include "math.h"
#include "asteroid.h"
#include "object.h"
#include "game.h"
#include "math.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "math.h"

using namespace math;

namespace model{

/** the asteroid class models an asteroid in space */
class asteroid: public object{
   private:
	Vector3 spin;
	bool destruct;
	
   public:
	asteroid(); 		// constructor
	~asteroid();	//deconstructor
	void setSpin(float Sx, float Sy, float Sz);	//Set the spin in degrees
	Vector3 getSpin();	//Return spin
	void doStep(float t);	//Change in time t in the simulation, change to reflect
	void draw(); //Draws a solid sphere for now, may make mesh later
	void setDestroy(bool d);
	bool getDestroy();
	void destroy();	//Animation to destroy asteroid
	bool checkCollision(Point3 shipPosition, float shipSize);
	void initialize();
	void recreate();
};

};

#endif
