#ifndef SHIP_H
#define SHIP_H

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

	ship();
	~ship();	
  private:
	int health;
	int score; 
	Vector3 secondaryDirection;
};

};

#endif
