#include "projectile.h"

/** projectile constructor */
model::projectile::projectile(){

}

/** copy constructor */
// model::projectile::projectile(const projectile &copyin) {
// 	initialize(PROJECTILE_SPEED, ((object)copyin).getDirection(), ((object)copyin).getPosition());
// }

/** projectile deconstructor */
model::projectile::~projectile(){

}

/** method to draw the projectile */
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

/** set initial values of the projectile */
void model::projectile::initialize(float spd, Vector3 dir, Point3 pos){
	speed = PROJECTILE_SPEED;
	direction = dir;
	position = pos;
	size = PROJECTILE_SIZE;
	position.z = position.z - size;
}

