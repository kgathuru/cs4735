#ifndef SHIP_H
#define SHIP_H

namespace model{
class ship{
	public:
	void setHealth(int health);
	int getHealth();
	void setFacing(vector facing);
	vector getFacing();
	void setScore(int score);
	int getScore();
	void left();
	void right();
	void up();
	void down();
	void fire();

	
	ship();
	~ship();	
	private:
	int health;
	vector facing;
	int score; 

};

};

#endif
