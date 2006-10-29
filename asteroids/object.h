#ifndef OBJECT_H
#define OBJECT_H

namespace model{
class object{
	public:
	double speed();
	void setSpeed();
	double getSpeed();
	void setDirection();
	double getDirection();
	bool loadModel();
	bool isMesh();
	
	object();
	~object();	
	private:
	//model::world world;
};
//extern engine gameengine;
//extern view gameview;
};

#endif
