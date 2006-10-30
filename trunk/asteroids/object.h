#ifndef OBJECT_H
#define OBJECT_H

#include "math.h"

namespace model{
class object: public Mesh{
	public:
	double speed();
	void setSpeed();
	double getSpeed();
	void setDirection();
	double getDirection();
	object();
	//~object();	
	private:
	//model::world world;
};
//extern engine gameengine;
//extern view gameview;
};

#endif
