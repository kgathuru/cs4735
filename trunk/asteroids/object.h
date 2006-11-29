#ifndef OBJECT_H
#define OBJECT_H

#include "math.h"

using namespace math;

namespace model{

/** the object class sets the basic behaviour of an object in space */
class object: public Mesh{
  public:
	void setSpeed(float s);
	float getSpeed();
	void setDirection(float x, float y, float z);
	Vector3 getDirection();
	void setPosition(float x, float y, float z);
	Point3 getPosition();
	void setSize(float s);
	float getSize();
	void doStep(float t);	//Change in time t in the simulation, change to reflect
	object();
	~object();	
  protected:
	Vector3 direction;
	Point3 position;
	float speed;
	float size;
};

};

#endif
