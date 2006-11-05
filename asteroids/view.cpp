#include "view.h"
#include "engine.h"

view::view(){
	
}

/** initialize OpenGL environment */
void view::initView(int *argc,char**argv){
	glutInit (argc,argv);
	glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize (WIDTH,HEIGHT);
	glutCreateWindow ("Asteroids3D");
	glutDisplayFunc(&(view::display));
	//glutKeyboardFunc(&(gameEngine::keyboard));
}

void view::display(void){
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
	
	// set the camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-WIDTH/2, WIDTH/2, 0, HEIGHT, 0, DEPTH);

	//glViewport(-WIDTH/2, 0, WIDTH, HEIGHT);
	//gluPerspective(45,1,0,DEPTH);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(0, 5, -10, 0, 0, 0, 0.0, 1.0, 0.0);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the screen


	controller::gameEngine.theWorld.render();

	glEnd();
	glutSwapBuffers();
}

