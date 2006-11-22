#include "asteroid.h"

/** Constructor, assigns random values to fields */
model::asteroid::asteroid(){
	//Set speed to be the same for every asteroid
	speed = ASTEROID_SPEED;

	//Assuming direction is a Vector3
	direction.set(0.0,0.0,1.0);	//All move in the positive x direction
}

/** Deconstructor */
model::asteroid::~asteroid(){
    //this = NULL;
}

void model::asteroid:: initialize(){
	//Size is radius of the sphere that represents the asteroid
	int x,y,z;
 
	//Set speed to be the same for every asteroid
	speed = ASTEROID_SPEED;
	//Set direction to be the same for every asteroid
	//Assuming direction is a Vector3
	direction.set(0.0,0.0,1.0);	//All move in the positive x direction

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
	x = (rand() % (WORLD_WIDTH/2)); if(x%2 == 0) x = x*(-1);
	y = (rand() % WORLD_HEIGHT);
	//cout << "X:" << x << "\n";
	//z = -(rand() % WORLD_DEPTH);
	z = -((rand() % (WORLD_DEPTH*2)) + WORLD_DEPTH);
	setPosition(x,y,z);
}

void model::asteroid:: recreate(){
	//create asteroid anew and then initialize it
	//sorry Kate for messing these up, the two functions did exactly the same thing.
	initialize();
}

void model::asteroid:: setSpin(float Sx, float Sy, float Sz){
	spin.set(Sx,Sy,Sz);
}

Vector3 model::asteroid:: getSpin(){
	return spin;
}

void model::asteroid:: draw(){

	if(size > 0)
	{
		float angleRot = 5;//Rotate the asteroid by how much
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix(); //save initial matrix
		glRotatef(angleRot, spin.x, spin.y, spin.z);//Rotate mesh based on movement
		glTranslatef(position.x, position.y, position.z);//Move asteroid to position in space
		glScalef(size, size, size);//Asteroid mesh is within unit circle centered at origin, need to scale by size
		glutSolidSphere(1,15,15);//Asteroid is just a sphere for now, may make mesh later if time
		glPopMatrix();//return default matrix
	}
}


void model::asteroid:: destroy(){
	//Animation to remove asteroid
	//Needs to be better so player knows they've been hit
	for(float i = size; i >= 0; i--);{
		size = size - 0.5;
		draw();
	}
	size = 0;
	draw();
}

void model::asteroid:: doStep(float t){
	//call super (parent) doStep method 
	object::doStep(t);

	//do additional work for asteroid
	if (position.z > 0.0 && size > 0)
	{
		//cout<<"\nRECREATE\n";
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

	//See if it is less than the sum of the radius of the ship and asteroid
	if (distance <= shipSize + size){
		//Need to destroy the asteroid if it's true
		return true;
		//Call deconstructor outside of the method
	} 
	else 
	{ 
		return false;
	}
}
