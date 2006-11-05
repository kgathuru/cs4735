#include "world.h"

/**world constructor*/
model::world::world(){
	/** create asteroids */
	for (int i=0; i<INITIAL_NUM_ASTEROIDS; i++){
		asteroid astr;
		asteroids.push_back(astr);
	}
}

/**world deconstructor*/
model::world::~world(){
	//this = NULL;
}

void model::world::renderBackground(){
	//Set up space box

	//Tile background

}

/** renders the objects in the world */
void model::world::render(){
	/** render axes */
	glClear(GL_COLOR_BUFFER_BIT);
	// Draw the axes.
	glColor3f(1.0, 0.0, 0.0);  
	glBegin(GL_LINES);  // X axis (red).
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(5.0, 0.0, 0.0);
	glEnd();
	glColor3f(0.0, 1.0, 0.0);  
	glBegin(GL_LINES);  // Y axis (green).
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 5.0, 0.0);
	glEnd();
	glColor3f(0.0, 0.0, 1.0);  
	glBegin(GL_LINES);  // Z axis (blue).
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 5.0);
	glEnd();

	
	/** render asteroids */
	for (asteroid_iterator iter=asteroids.begin(); iter!=asteroids.end(); iter++){
		iter->readFile("SIMPBARN.3VN");
		iter->draw();
	} 
}

/** updates the objects as time progresses */
void model::world::update(){

}

/** starting point accessor method */ 
Vector3 model::world::getStartPoint(){

}

/** starting point mutator method */
void model::world::setStartPoint(Point3 v){
	
}

/** ending point accessor method */
Vector3 model::world::getEndPoint(){

}

/** ending point mutator method */
void model::world::setEndPoint(Point3 v){

}


