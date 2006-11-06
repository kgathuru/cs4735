#include "view.h"
#include "engine.h"

viewer::view::view(){
	
}

/** initialize OpenGL environment */
void viewer::view::initView(int *argc,char**argv){
	glutInit (argc,argv);
	glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize (WIDTH,HEIGHT);
	glutCreateWindow ("Asteroids3D");
	glutDisplayFunc(&(view::display));
	
        Point3 eye(4.0, 4.0, 4.0); 
        Point3 look(0.0, 0.0, 0.0); 
        Vector3 up(0.0, 1.0, 0.0);
	controller::engine::camera1.setShape(30.0f, 64.0f/48.0f, 0.5f, 50.0f);
	controller::engine::camera1.set(eye, look, up); // make the initial camera
	//glutKeyboardFunc(&(gameEngine::keyboard));
}

void viewer::view::display(void){
	// set properties of the surface material
	GLfloat mat_ambient[] = { 0.25f, 0.25f, 0.25f, 1.0f}; // copper
	GLfloat mat_diffuse[] = { 0.4f, 0.4f, 0.4f, 1.0f}; 
	GLfloat mat_specular[] = { 0.256777f, 0.137622f, 0.086014f, 1.0f};
	GLfloat mat_shininess[] = { 128.0f }; 
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	// set the light source properties
	GLfloat lightIntensity[] = {2.0f, 2.0f, 2.0f, 1.0f};
	GLfloat light_position[] = {10.0f, 10.0f, 10.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);
	
	//Set the window
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WIDTH/2, WIDTH/2, 0, HEIGHT, 0, DEPTH);
	
	//Set the camera
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(0, 0, -150, 0, HEIGHT/2, 0, 0.0, 1.0, 0.0);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the screen

	//controller::gameEngine.theWorld.render();
	controller::gameEngine.theWorld.renderBackground();

	glEnd();
	glutSwapBuffers();
}

/** camera constructor */
viewer::camera::camera() {
	viewAngle = 0.0;
	aspect = 1.0;
	nearDist = 1.0;
	farDist = 2.0;
	eye.set(1.0, 1.0, 1.0);
	u.set(0.0, 0.0, 1.0);
	v.set(0.0, 1.0, 0.0);
	n.set(-1.0, 0.0, 0.0);
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


