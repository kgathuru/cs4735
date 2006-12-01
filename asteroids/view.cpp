#include "view.h"

using controller::gameEngine;

/** constructor for view class */
viewer::view::view(){
	
}

/** initialize OpenGL environment */
void viewer::view::initView(int *argc,char**argv){
	glutInit (argc,argv);

	//set up opengl window
	glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize (WINDOW_WIDTH,WINDOW_HEIGHT);
	gameEngine.gameView.winIdMain = glutCreateWindow("Asteroids3D");
	glutDisplayFunc(&(view::display));
	
	// make the initial camera view
        Point3 eye(0, WORLD_HEIGHT/2, 950.0); 
        Point3 look(0, WORLD_HEIGHT/2, -2000.0); 
        Vector3 up(0.0, 1.0, 0.0);

	gameEngine.camera1.setView(ONBOARD_CAM);
	gameEngine.camera1.setShape(30.0f, WORLD_WIDTH/WORLD_HEIGHT, CAMERA_NEAR_DIST, CAMERA_FAR_DIST);
	gameEngine.camera1.set(eye, look, up); 

	//load textures
	string s = "spaceScene.bmp";
	int ret = pix[1].readBMPFile(s);  
        pix[1].setTexture(2001);

	string explode = "explodeSmall.bmp";
	ret = pix[2].readBMPFile(explode);
	pix[2].setTexture(2002);

	string asteroidTexture = "asteroidPattern.bmp";
	ret = pix[5].readBMPFile(asteroidTexture);
	pix[5].setTexture(2003);

	string shipTexture = "metalTexture.bmp";
	ret = pix[6].readBMPFile(shipTexture);
	pix[6].setTexture(2004);

	string shipTexture2 = "red.bmp";
	ret = pix[6].readBMPFile(shipTexture2);
	pix[6].setTexture(2005);

}

/** display the objects in the world */
void viewer::view::display(void){

	// set the light source properties
	GLfloat light_intensity[] = {0.5f, 0.5f, 0.5f, 0.5f};
	GLfloat light_position[] = {10.0f, 10.0f, 10.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_intensity);

	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);  // enable the light source
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST); // for removal of hidden surfaces
	glEnable(GL_NORMALIZE);  // normalize vectors for proper shading
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); //for nice perpective
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the screen
	
	//check camera view
	if (gameEngine.camera1.getView() == ONBOARD_CAM){
		Point3 eye = gameEngine.theWorld.serenity.getPosition();
		eye.z += gameEngine.theWorld.serenity.getSize()*10;
		eye.y += 100;
		//eye.y += gameEngine.theWorld.serenity.getSize()*2;
		//This way camera only moves in the z direction
		//Is this what we want?
		//eye.y = WORLD_HEIGHT/2;
		//eye.x = 0;
		/** \todo is it legal to turn a vector into a point like this? */
		/** I want to tell the camera to look where the spaceship is looking, how do I do it? */
		//Vector3 lookv =  gameEngine.theWorld.serenity.getDirection();
		//Point3 look(eye.x +lookv.x, eye.y +lookv.y, lookv.z +lookv.z); 
		Point3 look(eye.x, eye.y, eye.z - 500); 
		Vector3 up(0.0, 1.0, 0.0);
		gameEngine.camera1.set(eye, look, up);//fix camera to ship
	}

	/** render world */
	glViewport((WINDOW_WIDTH - WORLD_WIDTH)/2,(WINDOW_HEIGHT-WORLD_HEIGHT)/2, WORLD_HEIGHT, WORLD_WIDTH);
	gameEngine.theWorld.render();

	/** render text */
	// Use the whole window. 
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glDisable(GL_LIGHTING);
	
	// We are going to do some 2-D orthographic drawing.
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	GLdouble size, aspect;
	size = (GLdouble)((WINDOW_WIDTH >= WINDOW_HEIGHT) ? WINDOW_WIDTH : WINDOW_HEIGHT) / 2.0;
	if (WINDOW_WIDTH <= WINDOW_HEIGHT) {  
		aspect = (GLdouble)WINDOW_HEIGHT/(GLdouble)WINDOW_WIDTH;
		glOrtho(-size, size, -size*aspect, size*aspect, 0, WORLD_DEPTH+1000);
	} else {
		aspect = (GLdouble)WINDOW_WIDTH/(GLdouble)WINDOW_HEIGHT;
		glOrtho(-size*aspect, size*aspect, -size, size, 0, WORLD_DEPTH+1000);
	}
	
	/* Make the world and window coordinates coincide so that 1.0 in 
	   model space equals one pixel in window space.                 */
	glScaled(aspect, aspect, 1.0);

	// Now draw text relative to camera 
	Point3 pos = gameEngine.camera1.getEye();
	glTranslated(pos.x, pos.y, pos.z);
	controller::gameEngine.gameView.drawStatus();

	glEnable(GL_LIGHTING);
	glPopMatrix();
	//double buffering
	glutSwapBuffers();
}

/** helper function to return string from int */
char ret[255];
char* num2char(int value);
char* num2char(int value){
	string tmp;
	stringstream out;
	out << value;
	tmp = out.str();
	int j; char c;
	for (j = 0; j < tmp.length(); j++){
		c = tmp[j];
		ret[j] = c;
	}
	ret[j] = '\0';
	return ret;
}

/** print status string */
void viewer::view::drawStatus(){
	/** load fonts */
 	void* bitmap_fonts[] = {GLUT_BITMAP_TIMES_ROMAN_24, GLUT_BITMAP_HELVETICA_12};
 	char* bitmap_font_names[] = {"GLUT_BITMAP_TIMES_ROMAN_24", "GLUT_BITMAP_HELVETICA_12"};

	/** draw menu */
	glColor3f(0.9, 0.5, 0.9);
 	char* fileMenu[] = {"ASTEROIDS 3D 1.0 | Click Anywhere for Menu"};
 	glRasterPos2f(-250, 265);
 	controller::gameEngine.gameView.print_bitmap_string(bitmap_fonts[1], fileMenu[0]);
	
	/** draw game stats */
	glColor3f(0.9, 0.5, 0.9);

	if (gameEngine.pause){
		char* winner[] = {"PAUSED"};
		glRasterPos2f(-20, 200);
		print_bitmap_string(bitmap_fonts[0], winner[0]);
	}

  	switch (gameEngine.getStatus()){
	case GAME_START: //display game start
		{
		char* gameStart[] = {"Press Enter To Start"};
		glRasterPos2f(-100, 200);
		print_bitmap_string(bitmap_fonts[0], gameStart[0]);

		glColor3f(0.4, 0.5, 0.6);
		char* controls[] = {"Controls:"};
		char* spaceBar[] = {"space bar = fire laser"};
		char* accelerate[] = {"a = accelerate"};
		char* decelerate[] = {"z = decelerate"};
		char* arrows[] = {"move = arrow keys"};
		glRasterPos2f(-40, 30);
		print_bitmap_string(bitmap_fonts[0], controls[0]);
		glRasterPos2f(-100, 0);
		print_bitmap_string(bitmap_fonts[0], spaceBar[0]);
		glRasterPos2f(-60, -20);
		print_bitmap_string(bitmap_fonts[0], accelerate[0]);
		glRasterPos2f(-60, -40);
		print_bitmap_string(bitmap_fonts[0], decelerate[0]);
		glRasterPos2f(-60, -60);
		print_bitmap_string(bitmap_fonts[0], arrows[0]);
		glRasterPos2f(-60, -80);
		break;	
		}
	case GAME_OVER: //display game over screen
		{
		char* gameOver[] = {"Game Over"};
		glRasterPos2f(-50, 200);
		print_bitmap_string(bitmap_fonts[0], gameOver[0]);
		break;
		}
	case GAME_WON: //display "you won" screen 
		{
		char* winner[] = {"You Won!"};
		glRasterPos2f(-20, 200);
		print_bitmap_string(bitmap_fonts[0], winner[0]);
		break; 
		}
	case GAME_LEVEL1: //display level1 game play
		{
		char stats[255] = {'\n'};
		strcat(stats, "Health: ");
		strcat(stats, num2char(gameEngine.theWorld.serenity.getHealth()));
		strcat(stats, " Score: ");
		strcat(stats, num2char(gameEngine.theWorld.serenity.getScore()));
		strcat(stats, " Speed: ");
		strcat(stats, num2char((int) gameEngine.theWorld.serenity.getSpeed()));
		strcat(stats, "\n");
		
		glRasterPos2f(-250, -265);
		print_bitmap_string(bitmap_fonts[1], stats);

		printProgress((gameEngine.theWorld.serenity.getPosition().z/-WORLD_DEPTH)*100);
		break;
		}
	}
}

/** print bitmap string */
void viewer::view::print_bitmap_string(void* font, char* s){
   if (s && strlen(s)) {
      while (*s) {
         glutBitmapCharacter(font, *s);
         s++;
      }
   }
}

/** print progress bar */
void viewer::view::printProgress(float progressPercent){
	/** render progress bar */
	glPushMatrix();
	glTranslated(20, -265, 0);

	Point3 pos = gameEngine.camera1.getEye();

	GLfloat barW = 230;
	GLfloat barH = 10;

	//draw progress bar 
	glColor3f(0.1F,0.0F,0.6F);
	glBegin(GL_POLYGON);
		glVertex2f(2,2);
		glVertex2f((progressPercent*(barW-4)/100)+2,2);
		glVertex2f((progressPercent*(barW-4)/100)+2,barH-2);
		glVertex2f(2,barH-2);
	glEnd();

	//draw progress bar background
	glColor3f(0.3F,0.2F,0.6F);
	glBegin(GL_POLYGON);
		glVertex2f(0,0);
		glVertex2f(barW,0);
		glVertex2f(barW,barH);
		glVertex2f(0,barH);
	glEnd();

	glPopMatrix();
}

/** camera constructor */
viewer::camera::camera() {
	//viewAngle = 0.0;
	//aspect = 1.0;
	//nearDist = 1.0;
	//farDist = 20.0;
	//eye.set(1.0, 1.0, 1.0);
	//u.set(0.0, 0.0, 1.0);
	//v.set(0.0, 1.0, 0.0);
	//n.set(-1.0, 0.0, 0.0);
}

/** change camera view, use constants in game.h */
void viewer::camera::setView(CameraView cameraView){
	view = cameraView;
}

/** change camera view, use constants in game.h */
CameraView viewer::camera::getView(){
	return view;
}

/** load modelview matrix with existing camera values */
void viewer::camera::setModelViewMatrix(void){ 
	float m[16];
	Vector3 eVec(eye.x, eye.y, eye.z); // a vector version of eye 
	m[0] =  u.x; m[4] =  u.y; m[8]  =  u.z;  m[12] = -eVec.dot(u);
	m[1] =  v.x; m[5] =  v.y; m[9]  =  v.z;  m[13] = -eVec.dot(v);
	m[2] =  n.x; m[6] =  n.y; m[10] =  n.z;  m[14] = -eVec.dot(n);
	m[3] =  0;   m[7] =  0;   m[11] =  0;    m[15] = 1.0;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m); // load OpenGLs modelview matrix
}

/** create a modelview matrix and send it to OpenGL */
void viewer::camera::set(Point3 Eye, Point3 look, Vector3 up){
	eye.set(Eye); // store the given eye position
        n.set(eye.x - look.x, eye.y - look.y, eye.z - look.z); // make n
	u.set(up.cross(n)); // make u = up X n
	n.normalize(); u.normalize(); // make them unit length
	v.set(n.cross(u));  // make v =  n X u
	setModelViewMatrix(); // tell OpenGL 
}

/** define shape of view volume */
void viewer::camera::setShape(float vAng, float asp, float nearD, float farD){
	viewAngle = vAng;
	aspect = asp;
	nearDist = nearD;
	farDist = farD;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(viewAngle, aspect, nearDist, farDist);  // tell OpenGL
}

/** slide the camera along its own axes */
void viewer::camera::slide(float delU, float delV, float delN){ 
	eye.x += delU * u.x + delV * v.x + delN * n.x;
	eye.y += delU * u.y + delV * v.y + delN * n.y;
	eye.z += delU * u.z + delV * v.z + delN * n.z;
	setModelViewMatrix(); // tell OpenGL 
}

/** roll the camera through angle degrees */
void viewer::camera::roll(float angle){ 
	float cs = cos(PI/180 * angle);
	float sn = sin(PI/180 * angle);
	Vector3 t = u;  // remember u
	u.set(cs*t.x - sn*v.x, cs*t.y - sn*v.y, cs*t.z - sn*v.z);
	v.set(sn*t.x + cs*v.x, sn*t.y + cs*v.y, sn*t.z + cs*v.z);
	setModelViewMatrix(); // tell OpenGL
}

/** roll the camera through angle degrees */
void viewer::camera::pitch(float angle){ 
	float cs = cos(angle);
	float sn = sin(angle);
	Vector3 t = v;  // remember u
	v.set(cs*t.x - sn*n.x, cs*t.y - sn*n.y, cs*t.z - sn*n.z);
	n.set(sn*t.x + cs*n.x, sn*t.y + cs*n.y, sn*t.z + cs*n.z);
	setModelViewMatrix(); // tell OpenGL
}

/** roll the camera through angle degrees */
void viewer::camera::yaw(float angle) {
	float cs = cos(PI/180 * angle);
	float sn = sin(PI/180 * angle);
	Vector3 t = n;  // remember u
	n.set(cs*t.x - sn*u.x, cs*t.y - sn*u.y, cs*t.z - sn*u.z);
	u.set(sn*t.x + cs*u.x, sn*t.y + cs*u.y, sn*t.z + cs*u.z);
	setModelViewMatrix(); // tell OpenGL
}

/** get the z position of the eye */
Point3 viewer::camera::getEye(){
	return eye;
}

