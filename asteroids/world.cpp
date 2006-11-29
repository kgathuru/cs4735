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
	static int count =0;
	glMaterialfv(GL_FRONT, GL_EMISSION, default_emissive); //default light emission

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
	
	Point3 pos = serenity.getPosition();
	float progress = (pos.z / -WORLD_DEPTH) * 100;
	Point3 position = controller::gameEngine.theWorld.serenity.getPosition();
	

	glPushMatrix();
	//float xSpot = WINDOW_WIDTH - pos.x;
	//glTranslated(-250, 0,0);
	glTranslated(pos.x -137, 0, 0);
	glTranslated(0, pos.y-40, 0);
	glTranslated(0, 0, pos.z-10);//serenity.getSize()*2);
	/** render progress bar */
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, 2003);   // choose the texture to use.
	glBegin(GL_QUADS); // begin drawing a square
	  glTexCoord2f(-1.0, -1.0); glVertex3f(0, -16,0);
  	  glTexCoord2f(-1.0, 1.0); glVertex3f(0,16,0);
 	  glTexCoord2f(1.0, 1.0); glVertex3f( progress,16,0);
	  glTexCoord2f(1.0, -1.0); glVertex3f( progress, -16,0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	/** render outer progress bar */
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, 2004);   // choose the texture to use.
	glBegin(GL_QUADS);		                // begin drawing a square   
	  glTexCoord2f(-1.0, -1.0); glVertex3f(0, -16,0);
  	  glTexCoord2f(-1.0, 1.0); glVertex3f(0,16,0);
 	  glTexCoord2f(1.0, 1.0); glVertex3f( serenity.getSize()*2,16, 0);//x was windowwidth
	  glTexCoord2f(1.0, -1.0); glVertex3f( serenity.getSize()*2, -16, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	
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

	glDisable(GL_LIGHTING);	//Allow colors to be drawn regardless of light
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
	for (asteroid_iterator iter=asteroids.begin(); iter!=asteroids.end(); iter++){
		iter->draw();
	} 

	
	/** render projectiles */
	glMaterialfv(GL_FRONT, GL_SPECULAR, projectile_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, projectile_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, projectile_diffuse);	
	glMaterialfv(GL_FRONT, GL_SHININESS, projectile_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, projectile_emissive);

	for (projectile_iterator iter=projectiles.begin(); iter!=projectiles.end(); iter++){
		iter->draw();
	} 

	Point3 p = serenity.getPosition();
	if(p.z <= -WORLD_DEPTH+100){
		drawWinner();
	}

	if(serenity.getHealth() < 1){
		drawGameOver();	
	}
 
	GLdouble size;
	GLdouble aspect;
	
	/* Use the whole window. */
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	
	/* We are going to do some 2-D orthographic drawing. */
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	size = (GLdouble)((WINDOW_WIDTH >= WINDOW_HEIGHT) ? WINDOW_WIDTH : WINDOW_HEIGHT) / 2.0;

	if (WINDOW_WIDTH <= WINDOW_HEIGHT) {  
		glPopMatrix(); 
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		aspect = (GLdouble)WINDOW_HEIGHT/(GLdouble)WINDOW_WIDTH;
		glOrtho(-size, size, -size*aspect, size*aspect, -100000.0, 100000.0);
	}
	else {
		aspect = (GLdouble)WINDOW_WIDTH/(GLdouble)WINDOW_HEIGHT;
		glOrtho(-size*aspect, size*aspect, -size, size, -100000.0, 100000.0);
	}

	/* Make the world and window coordinates coincide so that 1.0 in */
	/* model space equals one pixel in window space.                 */
	glScaled(aspect, aspect, 1.0);
	/* Now determine where to draw things. */
	
	glColor3f(1.0, 0, 0.0);
	glTranslated(pos.x -137, 0, 0);
	glTranslated(0, pos.y-40, 0);
	glTranslated(0, 0, pos.z-10);
	glBegin(GL_QUADS); // begin drawing a square
	  glVertex3f(0, -16,0);
  	  glVertex3f(0,16,0);
 	  glVertex3f( serenity.getSize()*3,16,0);
	  glVertex3f( serenity.getSize()*3,-16,0);
	glEnd();
	glColor3f(0.0, 0.0, 1.0);
	controller::gameEngine.theWorld.drawText();
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	//if(count == 500){
	//int mainWin = glutGetWindow();
	//		viewer::view::subDisplay();
	//		count = 0;
	//		glutSetWindow (mainWin); 
	//	}
	//	count++;
}


/** updates the objects as time progresses */
void model::world::update(){
	bool hit = false;
	/** update projectiles */
	projectile_iterator iter=projectiles.begin();
	while(iter!=projectiles.end())
	{
		iter->doStep(worldTime + GAME_SPEED);
		if(iter->getPosition().z <= -WORLD_DEPTH * 2)
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
				cout << "Projectile and asteroid destroyed\n";
				//cout << "NewNumAsteroids:" << projectiles.size() << "\n";

				//Destroy Projectile
				projIter->destroy();
				projIter = projectiles.erase(projIter);
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
			//cout << "ASTEROID HIT PROJECTILE\n";
			iter->destroy();
			//Only destroy for good when laser hits them
			iter->recreate();
			//Decrement ship health
			if(serenity.getHealth() - 1 == 0)
			{
				serenity.death();
				//Restart the game??
			}
			serenity.setHealth(serenity.getHealth() - 1);
			//Do something when the ship is hit to let player know
			serenity.hit();
		}
	
	} 
	
	glutPostRedisplay();
}

void model::world::print_bitmap_string(void* font, char* s){
   if (s && strlen(s)) {
      while (*s) {
         glutBitmapCharacter(font, *s);
         s++;
      }
   }
}

void model::world::drawText(void){
	static int font_index = 0;
	void* bitmap_fonts[1] = {GLUT_BITMAP_HELVETICA_12};
	char* bitmap_font_names[1] = {"GLUT_BITMAP_HELVETICA_12"};
	GLfloat y;
	
	/* Set up the strings with the characters to draw. */
	int health = serenity.getHealth();
	char* shipHealth[1] = {"Health: "};
	char* shipScore[1] = {"Score: "};
	char* shipSpeed[1] = {"Speed: "};
	
        string str;
	stringstream out;
	out << health;
	str = out.str();
	int j;
	int counter = 0;
	char c;
	char healthValue[2][3];
	for (j = 0; j < str.length(); j++){
		c = str[j];
		healthValue[1][j] = c;
		counter++;
	}
	healthValue[1][counter]= '\0';
	counter = 0;
    	int score = serenity.getScore(); 
	out << score;
	str = out.str();
	char scoreValue[2][3];
	for(j = 0; j < str.length(); j++){
		c = str[j];
		scoreValue[1][j] = c;
		counter++;
	}
	scoreValue[1][counter] = '\0';

	counter = 0;
	float speed = serenity.getSpeed();
	out << speed;
	str = out.str();
	char speedValue[2][3];
	for(j = 0; j < str.length(); j++){
		c = str[j];
		speedValue[1][j] = c;
		counter++;
	}
	speedValue[1][counter] = '\0';
	
	/* Draw the strings, according to the current mode and font. */
	glColor4f(0.0, 1.0, 0.0, 0.0);
	y = -140;

//	use this if not using sub windows
	glRasterPos2f(-140, y);
	print_bitmap_string(bitmap_fonts[font_index], shipHealth[0]);
	glRasterPos2f(-100, y);
	print_bitmap_string(bitmap_fonts[font_index], healthValue[1]);
	glRasterPos2f(-50, y);
	print_bitmap_string(bitmap_fonts[font_index], shipScore[0]);
	glRasterPos2f(-15, y);
	print_bitmap_string(bitmap_fonts[font_index], scoreValue[1]);
	glRasterPos2f(80, y);
	print_bitmap_string(bitmap_fonts[font_index], shipSpeed[0]);
	glRasterPos2f(120, y);
	print_bitmap_string(bitmap_fonts[font_index], speedValue[1]);

	//use this if using subwindows
	/**glRasterPos2f(1.0,0.0);
	print_bitmap_string(bitmap_fonts[font_index], shipHealth[0]);
	glRasterPos2f(3.0, 0);
	print_bitmap_string(bitmap_fonts[font_index], healthValue[1]);
	glRasterPos2f(6,0);
	print_bitmap_string(bitmap_fonts[font_index], shipScore[0]);
	glRasterPos2f(8,0);
	print_bitmap_string(bitmap_fonts[font_index], scoreValue[1]);
	glRasterPos2f(11,0);
	print_bitmap_string(bitmap_fonts[font_index], shipSpeed[0]);
	glRasterPos2f(13, 0);
	print_bitmap_string(bitmap_fonts[font_index], speedValue[1]);
*/
}

void model:: world:: drawGameOver(){
	static int font_index = 0;
	void* bitmap_fonts[1] = {GLUT_BITMAP_TIMES_ROMAN_24};
	char* bitmap_font_names[1] = {"GLUT_BITMAP_TIMES_ROMAN_24"};
	char* gameOver[1] = {"Game Over"};
	glRasterPos2f(-50, WINDOW_HEIGHT/2 -60);
	print_bitmap_string(bitmap_fonts[font_index], gameOver[0]);
}

void model:: world:: drawWinner(){
	static int font_index = 0;
	void* bitmap_fonts[1] = {GLUT_BITMAP_TIMES_ROMAN_24};
	char* bitmap_font_names[1] = {"GLUT_BITMAP_TIMES_ROMAN_24"};
	char* winner[1] = {"WINNER!"};
	glRasterPos2f(-50, WINDOW_HEIGHT/2 -60);
	print_bitmap_string(bitmap_fonts[font_index], winner[0]);
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

