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

namespace model{

class asteroid: public object{
   private:
	Vector3 spin;
	
   public:
	asteroid(); 		// constructor
	~asteroid();	//deconstructor
	void setSpin(float Sx, float Sy, float Sz);	//Set the spin in degrees
	Vector3 getSpin();	//Return spin
	void doStep(float t);	//Change in time t in the simulation, change to reflect
	void draw(); //Draws a solid sphere for now, may make mesh later
	void destroy();	//Animation to destroy asteroid
	bool checkCollision(Point3 shipPosition, float shipSize);
	void initialize();
	void recreate();
};

};

#endif
