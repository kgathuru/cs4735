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
	glPushMatrix(); //save initial matrix
	glTranslatef(position.x, position.y, position.z);//Move asteroid to position in space
	glutSolidTeapot(15); 
	glPopMatrix(); //regain initial matrix
}

void model::projectile::initialize(float spd, Vector3 dir, Point3 pos){
	speed = 10;
	direction = dir;
	position = pos;
}
