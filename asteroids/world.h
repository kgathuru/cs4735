#ifndef WORLD_H
#define WORLD_H

#include "math.cpp"
#include "object.cpp"
#include "game.h"
#include <list> 
#include "asteroid.cpp"

namespace model{

class world{
  public:
	Vector3 getStartPoint();
	void setStartPoint(Point3 v);
	Vector3 getEndPoint();
	void setEndPoint(Point3 v);
	void render();
	void update();
	
	/** STL list of asteroids */
	list<asteroid> asteroids;
	typedef list<asteroid>::iterator asteroid_iterator;
	
	/** \todo add more methods from UML */ 	
	world();
	~world();	
  private:
	
};

};

#endif
