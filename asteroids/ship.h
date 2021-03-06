#ifndef SHIP_H
#define SHIP_H

#include "projectile.h"
#include "math.h"

using namespace math;

namespace model{

/** the ship class models a spaceship in space */
class ship: public object {
  public:
	int getHealth();
	void setScore(int s);
	int getScore();
	void yaw(float angle);
	void pitch(float angle);
	void fire();
	void draw();
	void doStep(float t);
	void rubberBand();
	void setSecondaryDirection(float x, float y, float z);
	Vector3 getSecondaryDirection();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void accelerate();
	void deccelerate();
	void hit(int amount);
	void setReload(int r);
	int getReload();
	void rocketShip();

	ship();
	~ship();	
  private:
	int health;
	int score; 
	int reload;
	int damage;
	Vector3 secondaryDirection;
};

};

#endif
