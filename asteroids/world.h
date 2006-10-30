#ifndef WORLD_H
#define WORLD_H

#include "math.cpp"
#include "object.cpp"
//#include "asteroid.cpp"

namespace model{

class world{
	public:
	Vector3 getStartPoint();
	void setStartPoint();
	Vector3 getEndPoint();
	void setEndPoint();
	object spacebarn;
	//asteroid asteroid[NUM_ASTEROIDS]; 

	/** \todo add more methods from UML */ 	
	world();
	~world();	
	private:
};

};

#endif
