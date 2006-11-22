#ifndef SHIP_H
#define SHIP_H

#include "projectile.h"
#include "math.h"

namespace model{
class ship: public object {
  public:
	void setHealth(int h);
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
	void death();
	void hit();
	void setReload(int r);
	int getReload();

	ship();
	~ship();	
  private:
	int health;
	int score; 
	int reload;
	Vector3 secondaryDirection;
};

};

#endif
