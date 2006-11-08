#ifndef SHIP_H
#define SHIP_H

namespace model{
class ship: public object {
	public:
	void setHealth(int health);
	int getHealth();
	void setScore(int score);
	int getScore();
	void yaw(float angle);
	void pitch(float angle);
	void fire();
	void draw();
	void doStep(float t);

	ship();
	~ship();	
	private:
	int health;
	Vector3 x;
	int score; 
};

};

#endif
