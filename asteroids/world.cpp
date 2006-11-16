#include "world.h"

/**world constructor*/
model::world::world(){
	/** initialise variables */
	worldTime = 0.01;
	
	/** create asteroids */
	srand((unsigned)time(0));
	int x,y,z;
	for (int i=0; i<INITIAL_NUM_ASTEROIDS; i++){
		asteroid astr;
		astr.initialize();
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
	glDisable(GL_LIGHTING);	//Allow colors to be drawn regardless of light
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
	glEnable(GL_LIGHTING);	//Turn light back on, drawing done

	/** render ship */
	glMaterialfv(GL_FRONT, GL_SPECULAR, ship_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ship_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ship_diffuse);	
	glMaterialfv(GL_FRONT, GL_SHININESS, ship_shininess);

	serenity.draw();

	/** render asteroids */
	glMaterialfv(GL_FRONT, GL_SPECULAR, asteroid_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, asteroid_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, asteroid_diffuse);	
	glMaterialfv(GL_FRONT, GL_SHININESS, asteroid_shininess);

	for (asteroid_iterator iter=asteroids.begin(); iter!=asteroids.end(); iter++){
		iter->draw();
	} 
}

/** updates the objects as time progresses */
void model::world::update(){

	/** update asteroids */
	for (asteroid_iterator iter=asteroids.begin(); iter!=asteroids.end(); iter++){
		iter->doStep(worldTime + GAME_SPEED);
	} 

	/** update ship */
	serenity.doStep(worldTime + GAME_SPEED);

	//CHECK COLLISIONS BETWEEN EVERY ASTEROID AND THE SHIP
	for (asteroid_iterator iter=asteroids.begin(); iter!=asteroids.end(); iter++){
		//Just in case asteroid isn't destroyed, don't count it if size is 0
		if(iter->getSize() > 0)
		{		
			//returns true if there is a collision
			if(iter->checkCollision(serenity.getPosition(), serenity.getSize()))
			{
				//cout << "ASTEROID HIT SHIP\n";
				iter->destroy();
				//Do we want to recreate asteroids when they hit the ship or not? Only destroy for good when laser hits them?
				iter->recreate();
				//Decrement ship health
				serenity.setHealth(serenity.getHealth() - 1);
				//Do something when the ship is hit to let player know
				serenity.hit();
				//Do something if the ship dies
				if(serenity.getHealth() == 0)
				{
					serenity.death();
				}

			}
		}
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

