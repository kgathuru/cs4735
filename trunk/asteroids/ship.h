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

	ship();
	~ship();	
  private:
	int health;
	int score; 
};

};

#endif
