#include "world.h"
 
/**world constructor*/
model::world::world(){
	// initialise variables 
	worldTime = 0.01;

	//initialise randomizer
	srand((unsigned)time(0));

	// create asteroids 
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
	//set default light emission material
	glMaterialfv(GL_FRONT, GL_EMISSION, default_emissive); 

	/** render spacebackground */
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, 2001);   // choose the texture to use.
	glBegin(GL_QUADS);		                // begin drawing a square   
	  glTexCoord2f(0.0, 0.0); glVertex3f(-WORLD_WIDTH*6, -WORLD_HEIGHT*6, -WORLD_DEPTH-1000);
  	  glTexCoord2f(0.0, 1.0); glVertex3f(-WORLD_WIDTH*6,WORLD_HEIGHT*6,-WORLD_DEPTH-1000);
 	  glTexCoord2f(1.0, 1.0); glVertex3f( WORLD_WIDTH*6,WORLD_HEIGHT*6, -WORLD_DEPTH-1000);
	  glTexCoord2f(1.0, 0.0); glVertex3f( WORLD_WIDTH*6, -WORLD_HEIGHT*6, -WORLD_DEPTH-1000);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	/** render axes */
	/*
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
	*/

	/** render world box */
	glDisable(GL_LIGHTING);	//Allow colors to be drawn regardless of light
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1);
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
	for (asteroid_iterator iter=asteroids.begin(); iter!=asteroids.end(); iter++){
		iter->draw();
	} 

	/** render crosshairs*/
	Point3 crosshair = gameEngine.theWorld.serenity.getPosition();
	glDisable(GL_LIGHTING);	//Allow colors to be drawn regardless of light
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(2);
	glBegin(GL_LINES);
		glVertex3f(crosshair.x - 25, crosshair.y, crosshair.z - 1500);
		glVertex3f(crosshair.x + 25, crosshair.y, crosshair.z - 1500);
		glVertex3f(crosshair.x, crosshair.y + 25, crosshair.z - 1500);
		glVertex3f(crosshair.x, crosshair.y - 25, crosshair.z - 1500);
	glEnd();	
	glEnable(GL_LIGHTING);

	
	/** render projectiles */
	glMaterialfv(GL_FRONT, GL_SPECULAR, projectile_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, projectile_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, projectile_diffuse);	
	glMaterialfv(GL_FRONT, GL_SHININESS, projectile_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, projectile_emissive);

	for (projectile_iterator iter=projectiles.begin(); iter!=projectiles.end(); iter++){
		iter->draw();
	} 
}


/** updates the objects as time progresses */
void model::world::update(){
	bool hit = false;
	/** update projectiles */
	projectile_iterator iter=projectiles.begin();
	while(iter!=projectiles.end())
	{
		iter->doStep(worldTime + GAME_SPEED);
		if(iter->getPosition().z <= -WORLD_DEPTH)
		{
			//Destroy the projectile when it goes off screen
			//iter->destroy();
			iter = projectiles.erase(iter);
		}
		else
		{
			iter++;
		}
	} 

	if(projectiles.size() > 0)
	{
	//CHECK COLLISIONS BETWEEN EVERY ASTEROID AND EVERY PROJECTILE
	asteroid_iterator iter=asteroids.begin();
	while(iter!=asteroids.end())
	{
		//cout << "NUMPROJECTILES" << projectiles.size() << "\n";
		projectile_iterator projIter=projectiles.begin();
		projectile_iterator projIter2;
		while(projIter!=projectiles.end())	
		{
			//cout << "CHECK EACH PROJECTILE\n";
			//returns true if there is a collision
			if(iter->checkCollision(projIter->getPosition(),projIter->getSize()))
			{
						
				//Projectile hits asteroid, destroy both
				//Destroy Asteroid
				//iter = asteroids.erase(iter);
				hit = true;
			
				iter->setDestroy(true);
				//cout << "Projectile and asteroid destroyed\n";
				//cout << "NewNumAsteroids:" << projectiles.size() << "\n";

				//Destroy Projectile
				projIter->destroy();
				projIter = projectiles.erase(projIter);
				serenity.setScore(serenity.getScore() + 100);
			} else {
				iter->setDestroy(false);
				projIter++;
			}
			
		}
		if(!hit)
		{
			//iter->setDestroy(false);
			iter++;
		}
		hit = false;
	} //end while

	}//end if


	/** update asteroids */
	for (asteroid_iterator iter=asteroids.begin(); iter!=asteroids.end(); iter++){
		//if destroyed and size < 0 remove from list
		if (iter->getSize() < 0) {
			iter = asteroids.erase(iter);
		}
		iter->doStep(worldTime + GAME_SPEED);
	} 

	/** update ship */
	serenity.doStep(worldTime + GAME_SPEED);
	//CHECK COLLISIONS BETWEEN EVERY ASTEROID AND THE SHIP
	for (asteroid_iterator iter=asteroids.begin(); iter!=asteroids.end(); iter++){	
		//returns true if there is a collision
		if(iter->checkCollision(serenity.getPosition(), serenity.getSize()))
		{
			if(serenity.getHealth() - 1 == 0)
			{
				serenity.death();
				//gameEngine.setStatus(GAME_OVER);
			}
			serenity.setHealth(serenity.getHealth() - (int)(iter->getSize()/4));

			//cout << "ASTEROID HIT PROJECTILE\n";
			iter->destroy();
			//Only destroy for good when laser hits them
			iter->recreate();
			//Decrement ship health

			//Do something when the ship is hit to let player know
			
			//do we want to decrease the score when the ship gets hit?
			//probably just want to decrease health
			if(serenity.getScore() -1 > 0){
			  serenity.setScore(serenity.getScore()-1);
			}
			serenity.hit();

		}
	
	} 

	/** update status */
// 	Point3 p = serenity.getPosition();
// 	if(p.z <= -WORLD_DEPTH+100){
// 		drawWinner();
// 	}
// 
// 	if(serenity.getHealth() < 1){
// 		drawGameOver();	
// 	}
	
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

