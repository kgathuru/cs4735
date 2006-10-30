#ifndef WORLD_H
#define WORLD_H

#include "math.cpp"
#include "object.cpp"
#include "asteroid.cpp"

namespace model{

class world{
	public:
	Vector3 pathStart();
	Vector3 pathEnd();
	object testpawn;
	//asteroid asteroid[NUM_ASTEROIDS]; 
	double height();
	double width();
	double depth();
	/** \todo add more methods from UML */ 	
	world();	
	private:
};

};

#endif
