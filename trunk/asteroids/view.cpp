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
	GLfloat light_position[] = {2.0f, 6.0f, 3.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);
	// set the camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(-WIDTH/2, WIDTH/2, 0, HEIGHT);

	double winHt = 10;  // half-height of the window
	
	gluPerspective(60,1,0.001,10000);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	

	gluLookAt(2.3, 2.0, 2.5, 0, 0.5, 0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the screen

	//for each object in world.objects{
	//extern controller::engine gameEngine;
	//controller::gameEngine.theWorld.spacebarn.readFile("SIMPBARN.3VN");
	//controller::gameEngine.theWorld.spacebarn.draw();
	//}	

	glEnd();				// Done Drawing The Pyramid
	glutSwapBuffers();
}

