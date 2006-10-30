#ifndef PROJECTILE_H
#define PROJECTILE_H

namespace model{
class projectile{
	public:
	void setLifetime();
	int getLifetime();
	
	projectile();
	~projectile();	
	private:
	int lifetime;

};

};

#endif