#include "view.h"

using controller::gameEngine;

/** constructor for view class */
viewer::view::view(){
	
}

/** initialize OpenGL environment */
void viewer::view::initView(int *argc,char**argv){
	glutInit (argc,argv);
	glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize (WINDOW_WIDTH,WINDOW_HEIGHT);

	gameEngine.gameView.winIdMain = glutCreateWindow("Asteroids3D");
	glutDisplayFunc(&(view::display));
	
        Point3 eye(0, WORLD_HEIGHT/2, 950.0); 
        Point3 look(0, WORLD_HEIGHT/2, -2000.0); 
        Vector3 up(0.0, 1.0, 0.0);

	gameEngine.gameView.winIdSub2 = 
		glutCreateSubWindow (gameEngine.gameView.winIdMain, 0, 0, 50, WINDOW_HEIGHT / 20);
	glutDisplayFunc(&(view::subDisplay2));
	glutSetWindow(gameEngine.gameView.winIdMain);
	
	/* Sub window creation and setup */ 
	//gameEngine.gameView.winIdSub = 
	//	glutCreateSubWindow (gameEngine.gameView.winIdMain, 0, 550, WINDOW_WIDTH, WINDOW_HEIGHT / 20);
	//glutDisplayFunc(&(view::subDisplay));
	//glutSetWindow(gameEngine.gameView.winIdMain);

	/** \todo is aspect ratio based on world width or window width? */
	gameEngine.camera1.setView(DEFAULT_CAM);
	gameEngine.camera1.setShape(30.0f, WORLD_WIDTH/WORLD_HEIGHT, CAMERA_NEAR_DIST, CAMERA_FAR_DIST);
	gameEngine.camera1.set(eye, look, up); // make the initial camera

	string s = "spaceScene.bmp";
	int ret = pix[1].readBMPFile(s);  // make pixmap from image
        pix[1].setTexture(2001);

	string explode = "explodeSmall.bmp";
	ret = pix[2].readBMPFile(explode);
	pix[2].setTexture(2002);

	string progress = "progressBar1.bmp";
	ret = pix[3].readBMPFile(progress);
	pix[3].setTexture(2003);
	
	string moreProgress = "progressOuter.bmp";
	ret = pix[4].readBMPFile(moreProgress);
	pix[4].setTexture(2004);
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

	glViewport((WINDOW_WIDTH - WORLD_WIDTH)/2,(WINDOW_HEIGHT-WORLD_HEIGHT)/2, WORLD_HEIGHT, WORLD_WIDTH);
	gameEngine.theWorld.render();

	//glPushMatrix();
	//glTranslated(0, WORLD_HEIGHT/2, 0);
	//glScaled(10, 10, 10);
	//gameEngine.theWorld.serenity.rocketShip();
	//cout<<"DRAW ROCKET SHIP";
	//glPopMatrix();

	glutSwapBuffers();
}

void viewer::view::subDisplay(){ 
	//cout << "in subdisplay\n";
	/* Clear subwindow */ 
	glutSetWindow (gameEngine.gameView.winIdSub); 
	// glClearColor (1.0, 1.0, 1.0, 1.0); 
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	
	/* Draw border */ 
	glColor3f (0.0F, 1.0F, 0.0F); 
	glBegin (GL_LINE_LOOP); 
	glVertex2f (0.0F, 0.0F); 
	glVertex2f (0.0F, 0.99F); 
	glVertex2f (0.999F, 0.99F); 
	glVertex2f (0.999F, 0.0F); 
	glEnd (); 
	glColor3f (0.0F, 1.0F, 0.0F); 
	
	glViewport (0, 0, WINDOW_WIDTH, WINDOW_HEIGHT/10); 
	glMatrixMode (GL_PROJECTION); 
	glLoadIdentity (); 
	gluOrtho2D (0.0F, 30.0F, 0.0F, 30.0F); 
	
	//gameEngine.theWorld.drawGameOver();
	gameEngine.theWorld.drawText();
	glutSwapBuffers ();
}

void viewer::view::subDisplay2 () {
	cout << "in subdisplay2\n";

	/* Clear subwindow */
	// glutSetWindow (gameEngine.gameView.winIdSub2);
	// glClearColor (1.0, 1.0, 1.0, 1.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport (0, 0, WINDOW_WIDTH, WINDOW_HEIGHT/10);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D (0.0F, 30.0F, 0.0F, 30.0F);

	void* bitmap_fonts[1] = {GLUT_BITMAP_TIMES_ROMAN_24};
	char* bitmap_font_names[1] = {"GLUT_BITMAP_TIMES_ROMAN_24"};
	char* fileMenu[] = {"File "};
	glRasterPos2f(0, 0);
	gameEngine.theWorld.print_bitmap_string(bitmap_fonts[0], fileMenu[0]);
	
	glutSwapBuffers (); 
	glutSetWindow (gameEngine.gameView.winIdMain); 
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
void viewer::camera::setView(int view){
	cameraView = view;
}

/** change camera view, use constants in game.h */
int viewer::camera::getView(){
	return cameraView;
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
float viewer::camera::getEyeZ(){
	return eye.z;
}

