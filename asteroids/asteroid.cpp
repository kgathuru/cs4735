#include "object.h"
#include "math.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "mathlib.h"

//Constructor
asteroid::asteroid()
{
	//Size is radius of the sphere that represents the asteroid
	float sizeLimitUpper = 100;	//Upper size limit of asteroid
	float sizeLimitLower = 1; 	//Lower size limit of asteroid
	float x,y,z;
	float WIDTH, DEPTH, HEIGHT;
 
	//Set speed to be the same for every asteroid
	speed = 10.0;
	//Set direction to be the same for every asteroid
	//Assuming direction is a Vector3
	direction.set(1.0,0.0,0.0);	//All move in the positive x direction

	//Generate random size between upper and lower limit
	srand((unsigned)time(0));
	size = (rand()%sizeLimitUpper)+sizeLimitLower; 

	//Generate random spin for x, y, and z direction
	//Value in degrees, between 0 and 360 degrees
	x = (rand()%360);
	y = (rand()%360);
	z = (rand()%360);
	spin.set(x,y,z);

	//Set position randomly based on size of the world
	//Assuming that world path is the x axis
	z = (rand()%WIDTH);
	if(z%2 == 0)
		z = z*(-1)	
	y = (rand()%HEIGHT);
	x = (rand()%DEPTH);
	position.set(x,y,z);
}

//Deconstructor
asteroid::~asteroid()
{
    this = NULL;
}

void asteroid:: recreate()
{
	//Size is radius of the sphere that represents the asteroid
	float sizeLimitUpper = 100;	//Upper size limit of asteroid
	float sizeLimitLower = 1; 	//Lower size limit of asteroid
	float x,y,z;
	float WIDTH, DEPTH, HEIGHT;
 
	//Set speed to be the same for every asteroid
	speed = 10.0;
	//Set direction to be the same for every asteroid
	//Assuming direction is a Vector3
	direction.set(1.0,0.0,0.0);	//All move in the positive x direction

	//Generate random size between upper and lower limit
	srand((unsigned)time(0));
	size = (rand()%sizeLimitUpper)+sizeLimitLower; 

	//Generate random spin for x, y, and z direction
	//Value in degrees, between 0 and 360 degrees
	x = (rand()%360);
	y = (rand()%360);
	z = (rand()%360);
	spin.set(x,y,z);

	//Set position randomly based on size of the world
	//Assuming that world path is the x axis
	x = (rand()%WIDTH);
	if(z%x == 0)
		x = x*(-1)	
	y = (rand()%HEIGHT);
	z = (rand()%DEPTH);
	position.set(x,y,z);
}


void asteroid:: setSpin(float Sx, float Sy, float Sz)
{
	spin.set(Sx,Sy,Sz);
}

Vector3 asteroid:: getSpin()
{
	return spin;
}

void asteroid:: doStep(float t)
{
	float x,y,z;

	//change position to reflect movement
	x = position.x + t * direction.x;
	y = position.y + t * direction.y;
	z = position.z + t * direction.z;
	position.set(x,y,z);

	if(position.z < 0.0)
	{
		//Destroy asteroid
		destroy()
		//Reset fields and restart at end of path
		recreate();
	}

	//Need to check for collision with spaceship
	//Asteroids can't collide with each other, only ship
	
	//Draw new asteroid after collision detection
}

void asteroid:: draw()
{
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
}

void asteroid:: destroy()
{
	//Animation to remove asteroid
	for(float i = size; i > 0; i--);
	{
		size--;
		draw();
	}
}

bool asteroid:: checkCollision(Point3 shipPosition, float shipSize)
{
	//Find distance between two centers
	float distance;
	float dx, dy, dz;
	dx = postion.x - shipPosition.x;
	dy = postion.y - shipPosition.y;
	dz = postion.z - shipPosition.z;
	distance = sqrt(dx*dx + dy*dy + dz*dz);

	//See if it is less than the sum of the raduis of the ship and asteroid
	if(distance <= shipSize + size)
	{
		//Need to destroy the asteroid if it's true
		destroy();
		//call deconstructor
		~asteroid();
		
		return true;
	}
	else
	{
		return false;
	}
}