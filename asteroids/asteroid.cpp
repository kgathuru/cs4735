#include "asteroid.h"
#include "object.h"
#include "game.h"
#include "math.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "math.h"

/** Constructor, assigns random values to fields */
model::asteroid::asteroid(){
	//Set speed to be the same for every asteroid
	speed = 10.0;

	//Assuming direction is a Vector3
	direction.set(1.0,0.0,0.0);	//All move in the positive x direction
}

/** Deconstructor */
model::asteroid::~asteroid(){
    //this = NULL;
}

float model::asteroid::getSize(){
	return size;
}

void model::asteroid:: recreate(){
	//Size is radius of the sphere that represents the asteroid
	int x,y,z;
 
	//Set speed to be the same for every asteroid
	speed = 1.0;
	//Set direction to be the same for every asteroid
	//Assuming direction is a Vector3
	direction.set(1.0,0.0,0.0);	//All move in the positive x direction

	//Generate random size between upper and lower limit
	//srand((unsigned)time(0));
	size = (rand() % ASTEROID_MAX_SIZE) + ASTEROID_MIN_SIZE; 

	//Generate random spin for x, y, and z direction
	//Value in degrees, between 0 and 360 degrees
	x = (rand()%360);
	y = (rand()%360);
	z = (rand()%360);
	spin.set(x,y,z);

	//Set position randomly based on size of the world
	//Assuming that world path is the x axis
	x = (rand() % WORLD_WIDTH); if(x%2 == 0) x = x*(-1);
	y = (rand() % WORLD_HEIGHT);
	z = -((rand() % WORLD_DEPTH));//-((rand() % WORLD_DEPTH) + WORLD_DEPTH);
	position.set(x,y,z);
}

void model::asteroid:: setSpin(float Sx, float Sy, float Sz){
	spin.set(Sx,Sy,Sz);
}

Vector3 model::asteroid:: getSpin(){
	return spin;
}

void model::asteroid:: draw(){
	//save initial matrix
	glPushMatrix();
	//Rotate the asteroid by how much
	float angleRot = 5;
	//DRAW NEW ASTEROID
	glMatrixMode(GL_MODELVIEW);
	//Rotate mesh based on movement
	glRotatef(angleRot, spin.x, spin.y, spin.z);
	//Move asteroid to position in space
	glTranslatef(position.x, position.y, position.z);
	//Asteroid mesh is within unit circle centered at origin, need to scale by size
	glScalef(size, size, size);
	//Asteroid is just a sphere for now, may make mesh later if time
	glutSolidSphere(1,15,15);
	//return default matrix
	glPopMatrix();
}

void model::asteroid:: destroy(){
	//Animation to remove asteroid
	for(float i = size; i > 0; i--);{
		size--;
		draw();
	}
}

void model::asteroid:: doStep(float t){
	float x,y,z;

	//change position to reflect movement
	x = position.x + t * direction.x;
	y = position.y + t * direction.y;
	z = position.z + t * direction.z;
	position.set(x,y,z);

	if(position.z < 0.0)
	{
		//Destroy asteroid
		destroy();
		//Reset fields and restart at end of path
		recreate();
	}

	//Need to check for collision with spaceship
	//Asteroids can't collide with each other, only ship
	
	//Draw new asteroid after collision detection
}


bool model::asteroid:: checkCollision(Point3 shipPosition, float shipSize){
	//Find distance between two centers
	float distance;
	float dx, dy, dz;
	dx = position.x - shipPosition.x;
	dy = position.y - shipPosition.y;
	dz = position.z - shipPosition.z;
	distance = sqrt(dx*dx + dy*dy + dz*dz);

	//See if it is less than the sum of the raduis of the ship and asteroid
	if (distance <= shipSize + size){
		//Need to destroy the asteroid if it's true
		destroy();

		return true;
		//Call deconstructor outside of the method
	} else { return false; }
}
