#include "projectile.h"

/** projectile constructor */
model::projectile::projectile(){

}

/** projectile deconstructor */
/*model::projectile::~projectile(){

}*/

/** lifetime mutator method */ 
void model::projectile::setLifetime(){

}

/** lifetime accessor method */
int model::projectile::getLifetime(){

}

void model::projectile::draw(){
	if(size > 0)
	{
		glPushMatrix(); //save initial matrix	
		glTranslatef(position.x, position.y, position.z);//Move projectile to position in space	
		glScalef(0.5, 1, 3);
		glutSolidSphere(size, 10, 10);
		glPopMatrix(); //regain initial matrix
	}
} 

void model::projectile::initialize(float spd, Vector3 dir, Point3 pos){
	speed = PROJECTILE_SPEED;
	direction = dir;
	position = pos;
	size = PROJECTILE_SIZE;
	position.z = position.z - size;
}

void model::projectile::destroy(){
	size = 0;
	draw();
}

