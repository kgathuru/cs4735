#ifndef WORLD_H
#define WORLD_H

#include "math.h"
#include "object.h"
#include "game.h"
#include "asteroid.h"
#include "projectile.h"
#include "ship.h"
#include "iostream"
#include "GL/gl.h"
#include "GL/glut.h"
#include <list> 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <string>

using std::string;

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

	list<asteroid> asteroids; ///<STL list of asteroids
	typedef list<asteroid>::iterator asteroid_iterator; ///< asteroid iterator
	list<projectile> projectiles; ///< STL list of projectiles
	typedef list<projectile>::iterator projectile_iterator; ///< projectile iterator
	ship serenity; ///< the ship - originally named spacebarn, now named serenity

	world();
	~world();
  private:
	//double worldTime; ///< current time in the world
	Point3 startPoint; ///< starting point of game
	Point3 endPoint;
};

};

#endif
