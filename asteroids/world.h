#ifndef WORLD_H
#define WORLD_H

#include "math.cpp"
#include "object.cpp"
#include "game.h"
#include <list> 
#include "asteroid.cpp"
#include "ship.cpp"

namespace model{

class world{
  public:
	Point3 getStartPoint();
	void setStartPoint(Point3 v);
	Point3 getEndPoint();
	void setEndPoint(Point3 v);
	void render();
	void update();
	
	list<asteroid> asteroids;
	typedef list<asteroid>::iterator asteroid_iterator;
	
	ship serenity;

	/** \todo add more methods from UML */ 	
	world();
	~world();
  private:
	double worldTime;
	Point3 startPoint;
	Point3 endPoint;
};

};

#endif
