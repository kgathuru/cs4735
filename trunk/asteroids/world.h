#ifndef WORLD_H
#define WORLD_H

#include "math.h"
#include "object.h"
#include "game.h"
#include <list> 
#include "asteroid.h"
#include "ship.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

namespace model{

class world{
  public:
	Point3 getStartPoint();
	void setStartPoint(Point3 v);
	Point3 getEndPoint();
	void setEndPoint(Point3 v);
	void render();
	void renderPane();
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
