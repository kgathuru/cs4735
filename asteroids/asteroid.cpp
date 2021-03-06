#include "asteroid.h"

/** Constructor, assigns random values to fields */
model::asteroid::asteroid(){
	//Set speed to be the same for every asteroid
	speed = ASTEROID_SPEED;
	destruct = false;
	//Assuming direction is a Vector3
	direction.set(0.0,0.0,1.0);	//All move in the positive x direction
}

/** Deconstructor */
model::asteroid::~asteroid(){
    //this = NULL;
}

/** initialize asteroid values */
void model::asteroid:: initialize(){
	//Size is radius of the sphere that represents the asteroid
	int x,y,z;

	//Set initial angle of rotation
	angleRotate = 0.1;
 
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
	x = (rand()%100);
	y = (rand()%100);
	z = (rand()%100);
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

/** recreate the asteroid */
// void model::asteroid:: recreate(){
// 	//create asteroid anew and then initialize it
// 	//sorry Kate for messing these up, the two functions did exactly the same thing.
// 	//initialize();
// }

/** set the spin of the asteroid */
void model::asteroid:: setSpin(float Sx, float Sy, float Sz){
	spin.set(Sx,Sy,Sz);
}

/** spin accessor method */
Vector3 model::asteroid:: getSpin(){
	return spin;
}

/** angle mutator method */
void model::asteroid::setAngle(float a){
	angleRotate = a;
}

/** angle accessor method */
float model::asteroid::getAngle(){
	return angleRotate;
}

/** asteroid draw method */
void model::asteroid:: draw(){
	GLUquadricObj*	qobj;

	if (!destruct && size > 0) {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix(); //save initial matrix

		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glBindTexture(GL_TEXTURE_2D, 2003);   // choose the texture to use.
		qobj = gluNewQuadric();	
		gluQuadricDrawStyle(qobj, GLU_FILL);
        	gluQuadricNormals(qobj, GLU_SMOOTH);
        	gluQuadricTexture(qobj, GL_TRUE);

		glTranslatef(position.x, position.y, position.z);//Move asteroid to position in space

		glRotatef(angleRotate, spin.x/100, spin.y/100, spin.z/100);//Rotate mesh based on movement

		glScalef(size, size, size);//Asteroid mesh is within unit circle centered at origin, 
		//need to scale by size

		gluSphere(qobj, 1, 15, 15);
		glDisable(GL_TEXTURE_2D);

		//glutSolidSphere(1,15,15);//Asteroid is just a sphere for now
		glPopMatrix();//return default matrix
	} else if (destruct) {
		// render explosion bitmap 
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glBindTexture(GL_TEXTURE_2D, 2002);   // choose the texture to use.
		glBegin(GL_QUADS); // begin drawing a square
		glTexCoord2f(0.0,0.0); glVertex3f( position.x - (size/2), position.y - (size/2), position.z);
		glTexCoord2f(0.0,1.0); glVertex3f( position.x - (size/2), position.y + (size/2), position.z);
		glTexCoord2f(1.0,1.0); glVertex3f( position.x + (size/2), position.y + (size/2), position.z);
		glTexCoord2f(1.0,0.0); glVertex3f( position.x + (size/2), position.y - (size/2), position.z);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		size = size - 0.5;
	}
}

/** destroy mutator method 
	\param d value to set destroy to */
void model::asteroid:: setDestroy(bool d){
	destruct = d;
}

/** destroy accessor method */
bool model::asteroid:: getDestroy(){
	return destruct;
}

void model::asteroid:: doStep(float t){
	//call super (parent) doStep method 
	object::doStep(t);
	angleRotate += 0.1;

	//do additional work for asteroid
	if (position.z > 0.0 && size > 0)
	{
		//cout<<"\nRECREATE\n";
		//Destroy asteroid
		//destroy();
		//Reset fields and restart at end of path
		initialize();
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
	} else { 
		return false;
	}
}
