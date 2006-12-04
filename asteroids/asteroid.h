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
	float angleRotate;
	
   public:
	asteroid();
	~asteroid();
	void setSpin(float Sx, float Sy, float Sz);
	Vector3 getSpin();
	void doStep(float t);
	void draw(); 
	void setDestroy(bool d);
	bool getDestroy();
	void setAngle(float a);
	float getAngle();
	bool checkCollision(Point3 shipPosition, float shipSize);
	void initialize();
	//void recreate();
};

};

#endif
