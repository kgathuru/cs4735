#include "world.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**world constructor*/
model::world::world(){
	/** initialise variables */
	worldTime = 0.01;
	
	/** create asteroids */
	srand((unsigned)time(0));
	int x,y,z;
	for (int i=0; i<INITIAL_NUM_ASTEROIDS; i++){
		asteroid astr;

		//Generate random size between upper and lower limit
		astr.setSize((rand() % ASTEROID_MAX_SIZE) + ASTEROID_MIN_SIZE); 

		//Generate random spin for x, y, and z direction
		//Value in degrees, between 0 and 360 degrees
		x = (rand()%360);
		y = (rand()%360);
		z = (rand()%360);
		astr.setSpin(x,y,z);

		//Set position randomly based on size of the world
		//Assuming that world path is the x axis
		x = (rand() % (WORLD_WIDTH/2)); if(x%2 == 0) x = x*(-1);
		y = (rand() % WORLD_HEIGHT);
		//z = (-1)*(rand() % WORLD_DEPTH);
		z = -((rand() % WORLD_DEPTH) + WORLD_DEPTH);
		astr.setPosition(x,y,z);
		//cout<<x;cout<<"\n";cout<<y;cout<<"\n";cout<<z;cout<<"\n";
		asteroids.push_back(astr);
	}
}

/**world deconstructor*/
model::world::~world(){
	//this = NULL;
}

/** renders the objects in the world */
void model::world::render(){
	/** render axes */
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(2);
	glBegin(GL_LINES);  // X axis (red).
		glVertex3f(-(WORLD_WIDTH/2), 0.0, 0.0);
		glVertex3f(WORLD_WIDTH/2, 0.0, 0.0);
	glEnd();
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);  // Y axis (green).
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, WORLD_HEIGHT, 0.0);
	glEnd();
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);  // Z axis (blue).
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, -WORLD_DEPTH);
	glEnd();

	/** render world box */
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_STRIP);
		glVertex3f(-(WORLD_WIDTH/2), 0.0, 0.0);
		glVertex3f(WORLD_WIDTH/2, 0.0, 0.0);
		glVertex3f(WORLD_WIDTH/2, WORLD_HEIGHT, 0.0);
		glVertex3f(-(WORLD_WIDTH/2), WORLD_HEIGHT, 0.0);
		glVertex3f(-(WORLD_WIDTH/2), 0.0, 0.0);
		glVertex3f(-(WORLD_WIDTH/2), 0.0, -WORLD_DEPTH);
		glVertex3f(WORLD_WIDTH/2, 0.0, -WORLD_DEPTH);
		glVertex3f(WORLD_WIDTH/2, 0.0, 0.0);
	glEnd();
	glBegin(GL_LINE_STRIP);
		glVertex3f(WORLD_WIDTH/2, 0.0, -WORLD_DEPTH);
		glVertex3f(WORLD_WIDTH/2, WORLD_HEIGHT, -WORLD_DEPTH);
		glVertex3f(WORLD_WIDTH/2, WORLD_HEIGHT, 0.0);
		glVertex3f(-(WORLD_WIDTH/2), WORLD_HEIGHT, 0.0);
		glVertex3f(-(WORLD_WIDTH/2), WORLD_HEIGHT, -WORLD_DEPTH);
		glVertex3f(WORLD_WIDTH/2, WORLD_HEIGHT, -WORLD_DEPTH);
		glVertex3f(-(WORLD_WIDTH/2), WORLD_HEIGHT, -WORLD_DEPTH);
		glVertex3f(-(WORLD_WIDTH/2), 0.0, -WORLD_DEPTH);
	glEnd();

	/** render asteroids */
	for (asteroid_iterator iter=asteroids.begin(); iter!=asteroids.end(); iter++){
		iter->draw();
	} 
}

/** updates the objects as time progresses */
void model::world::update(){
	/** update asteroids */
	for (asteroid_iterator iter=asteroids.begin(); iter!=asteroids.end(); iter++){
		iter->doStep(worldTime + 0.01);
	} 
	glutPostRedisplay();
}

/** starting point accessor method */ 
Point3 model::world::getStartPoint(){
	return startPoint;
}

/** starting point mutator method */
void model::world::setStartPoint(Point3 v){
	startPoint.set(v);
}

/** ending point accessor method */
Point3 model::world::getEndPoint(){
	return endPoint;
}

/** ending point mutator method */
void model::world::setEndPoint(Point3 v){
	endPoint.set(v);
}

