#include "view.h"

view::view(){

}

void view::display(){

	for each object in world.objects{
		object.draw();
	}	

	glEnd();				// Done Drawing The Pyramid
	glutSwapBuffers();
}

