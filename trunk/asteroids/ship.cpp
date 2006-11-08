#include "ship.h"


/** ship constructor */
model::ship::ship(){
	readFile("SIMPBARN.3VN");
}

/** ship deconstructor */
model::ship::~ship(){

}

/** health mutator method */ 
void model::ship::setHealth(int health){

}

/** health accessor method */
int model::ship::getHealth(){

}

/** facing mutator method */ 
void model::ship::setFacing(Vector3 facing){

}

/** facing accessor method */
Vector3 model::ship::getFacing(){

}

/** score mutator method */ 
void model::ship::setScore(int score){

}

/** score accessor method */
int model::ship::getScore(){

}

/** method to move ship to the left*/ 
void model::ship::left(){

}

/** method to move ship to the right*/
void model::ship::right(){

}

/** method to move ship up*/
void model::ship::up(){

}

void model::ship::draw(){
	glPushMatrix();
	//draw position
	glRotated(-90, 1, 0, 0);
	glRotated(90, 0, 0, 1);
	glScaled(50, 50, 50);

	//call super.draw()
	Mesh::draw();
	glPopMatrix();
}

/** method to move ship to down*/
void model::ship::down(){

}

/** method to fire a projectile */
/** creates a projectile object*/
void model::ship::fire(){

}
