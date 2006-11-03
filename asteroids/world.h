#ifndef WORLD_H
#define WORLD_H

#include "math.cpp"
#include "object.cpp"
#include <list> 
//#include "asteroid.cpp"

namespace model{

class world{
	public:
	Vector3 getStartPoint();
	void setStartPoint(Point3 v);
	Vector3 getEndPoint();
	void setEndPoint(Point3 v);
	

	/** \todo change to asteroids when ready */
	list<object> asteroids;
	typedef list<object>::iterator asteroids_iter;
	
	//asteroid asteroid[INITAL_NUM_ASTEROIDS]; 

	/** \todo add more methods from UML */ 	
	world();
	~world();	
	private:
	
};

};

#endif
