#ifndef OBJECT_H
#define OBJECT_H

#include "math.h"

namespace model{
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
	object();
	~object();	
	protected:
	Vector3 direction;
	Point3 position;
	float speed;
	float size;
	//model::world world;
};
//extern engine gameengine;
//extern view gameview;
};

#endif
