#ifndef SHIP_H
#define SHIP_H

namespace model{
class ship: public object {
	public:
	void setHealth(int health);
	int getHealth();
	void setFacing(Vector3 facing);
	Vector3 getFacing();
	void setScore(int score);
	int getScore();
	void left();
	void right();
	void up();
	void down();
	void fire();
	void draw();

	ship();
	~ship();	
	private:
	int health;
	Vector3 facing;
	int score; 
};

};

#endif
