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
	glutSolidTeapot(size); 
	glPopMatrix(); //regain initial matrix
}

void model::projectile::initialize(float spd, Vector3 dir, Point3 pos){
	speed = spd * 5;
	direction = dir;
	position = pos;
	position.z = position.z - size;
}

void model::projectile::destroy()
{
	//Animation to remove asteroid
	//Needs to be better so player knows they've been hit
	for(float i = size; i >= 0; i--);{
		size--;
		draw();
	}
	size = 0;
}
