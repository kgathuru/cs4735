#include "object.h"

/** object constructor */
model::object::object(){
	//Mesh();
}

/** object destructor */
model::object::~object(){

}

/** speed mutator method */ 
void model::object::setSpeed(float s){
	speed = s;
}

/** speed accessor method */
float model::object::getSpeed(){
	return speed;
}

/** direction mutator method */
void model::object::setDirection(float x, float y, float z){
	direction.set(x,y,z);
}

/** direction accessor method */
Vector3 model::object::getDirection(){
	return direction;
}

void model::object::setPosition(float x, float y, float z){
	position.set(x,y,z);
}

Point3 model::object::getPosition(){
	return position;
}

void model::object::setSize(float s){
	size = s;
}

float model::object::getSize(){
	return size;
}

void model::object:: doStep(float t){
	position.set(
		position.x + t * speed * direction.x,
		position.y + t * speed * direction.y,
		position.z + t * speed * direction.z
	);
}
