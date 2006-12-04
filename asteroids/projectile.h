#ifndef PROJECTILE_H
#define PROJECTILE_H

using namespace math;

namespace model{

/** the projectile class models a projectile fired from the spaceship */ 
class projectile: public object{
	public:
	void initialize(float spd, Vector3 dir, Point3 pos);
	void draw();
	
	projectile();
// 	projectile(const projectile &copyin);
	~projectile();	
};

};

#endif
