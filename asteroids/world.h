#ifndef WORLD_H
#define WORLD_H

#include "math.h"
#include "object.h"
#include "game.h"
#include "asteroid.h"
#include "projectile.h"
#include "ship.h"
#include "iostream"
#include "string"
#include "GL/gl.h"
#include "GL/glut.h"
#include <list> 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <string>

using namespace math;

/** the model namespace contains classes that describe the objects in the game */
namespace model{

/** the world is the main object in the game, it contains the other objects */
class world{
  public:
	Point3 getStartPoint();
	void setStartPoint(Point3 v);
	Point3 getEndPoint();
	void setEndPoint(Point3 v);
	void render();
	void renderPane();
	void update();
	void print_bitmap_string(void* font, char* s);
        void drawText(void);	
	void drawGameOver(void);
	void drawWinner(void);

	list<asteroid> asteroids;
	typedef list<asteroid>::iterator asteroid_iterator;

	list<projectile> projectiles;
	typedef list<projectile>::iterator projectile_iterator;
	
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
