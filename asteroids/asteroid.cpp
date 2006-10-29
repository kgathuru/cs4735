#include "object.h"
#include "math.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

asteroid::asteroid()
{
	//Size is radius of the sphere that represents the asteroid
	float sizeLimitUpper = 100;	//Upper size limit of asteroid
	float sizeLimitLower = 1; 	//Lower size limit of asteroid
	float x,y,z;
	float 
 
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


void setSpin(float Sx, float Sy, float Sz)
{
	spin.set(Sx,Sy,Sz);
}

Vector3 getSpin()
{
	return spin;
}

void doStep(float t)
{
	//change position to reflect movement
	
}