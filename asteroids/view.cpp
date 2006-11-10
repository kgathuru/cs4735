#include "view.h"

viewer::view::view(){
	
}

/** initialize OpenGL environment */
void viewer::view::initView(int *argc,char**argv){
	glutInit (argc,argv);
	glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize (WINDOW_WIDTH,WINDOW_HEIGHT);

	glutCreateWindow ("Asteroids3D");
	glutDisplayFunc(&(view::display));
	glutOverlayDisplayFunc(displayFunc);
	
	//Make the world bigger so things don't get clipped moving around
	/** sorry kate, when we use the camera it sets up its own glperspective */
	//glOrtho(-WORLD_WIDTH, WORLD_WIDTH, -WORLD_HEIGHT*2, WORLD_HEIGHT*2, WORLD_DEPTH, -WORLD_DEPTH*2);
	
        Point3 eye(0, WORLD_HEIGHT/2, 950.0); 
        Point3 look(0, WORLD_HEIGHT/2, -2000.0); 
        Vector3 up(0.0, 1.0, 0.0);

	/** \todo is aspect ratio based on world width or window width? */
	controller::gameEngine.camera1.setView(DEFAULT_CAM);
	controller::gameEngine.camera1.setShape(30.0f, WORLD_WIDTH/WORLD_HEIGHT, 100.0f, 4000.0f);
	controller::gameEngine.camera1.set(eye, look, up); // make the initial camera
}

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
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the screen

	//check camera view
	if (controller::gameEngine.camera1.getView() == ONBOARD_CAM){
		Point3 eye = controller::gameEngine.theWorld.serenity.getPosition();
		/** \todo is it legal to turn a vector into a point like this? */
		/** I want to tell the camera to look where the spaceship is looking, how do I do it? */
		Vector3 lookv = controller::gameEngine.theWorld.serenity.getDirection();
		Point3 look(eye.x + lookv.x, eye.y + lookv.y, look.z + lookv.z); 
		Vector3 up(0.0, 1.0, 0.0);
		controller::gameEngine.camera1.set(eye, look, up);//fix camera to ship
	}
	
	
	glViewport((WINDOW_WIDTH - WORLD_WIDTH)/2,(WINDOW_HEIGHT-WORLD_HEIGHT)/2, WORLD_HEIGHT, WORLD_WIDTH);
	controller::gameEngine.theWorld.render();

	glutSwapBuffers();
}

void viewer::view::displayFunc(void){

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	glDisable(GL_LIGHTING);	//Allow colors to be drawn regardless of light
	glDisable(GL_LIGHT0);
	glColor3f(1.0, 1.0, 1.0);

	//glViewport(0,0,WINDOW_WIDTH,(WINDOW_HEIGHT-WORLD_HEIGHT)/2);
	glBegin(GL_POLYGON);
		glVertex2d(0.0, 0.0);
		glVertex2d(0.0, WINDOW_HEIGHT);
		glVertex2d(WINDOW_WIDTH, WINDOW_HEIGHT);
		glVertex2d(WINDOW_WIDTH, 0.0);
		glVertex2d(0.0, 0.0);
	glEnd();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glFlush();
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
	float cs = cos(3.141592653589793/180 * angle);
	float sn = sin(3.141592653589793/180 * angle);
	Vector3 t = u;  // remember u
	u.set(cs*t.x - sn*v.x, cs*t.y - sn*v.y, cs*t.z - sn*v.z);
	v.set(sn*t.x + cs*v.x, sn*t.y + cs*v.y, sn*t.z + cs*v.z);
	setModelViewMatrix(); // tell OpenGL
}

/** roll the camera through angle degrees */
void viewer::camera::pitch(float angle){ 
	float cs = cos(3.141592653589793/180 * angle);
	float sn = sin(3.141592653589793/180 * angle);
	Vector3 t = v;  // remember u
	v.set(cs*t.x - sn*n.x, cs*t.y - sn*n.y, cs*t.z - sn*n.z);
	n.set(sn*t.x + cs*n.x, sn*t.y + cs*n.y, sn*t.z + cs*n.z);
	setModelViewMatrix(); // tell OpenGL
}

/** roll the camera through angle degrees */
void viewer::camera::yaw(float angle) {
	float cs = cos(3.141592653589793/180 * angle);
	float sn = sin(3.141592653589793/180 * angle);
	Vector3 t = n;  // remember u
	n.set(cs*t.x - sn*u.x, cs*t.y - sn*u.y, cs*t.z - sn*u.z);
	u.set(sn*t.x + cs*u.x, sn*t.y + cs*u.y, sn*t.z + cs*u.z);
	setModelViewMatrix(); // tell OpenGL
}


