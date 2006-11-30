#ifndef VIEW_H
#define VIEW_H

#include <GL/glut.h>
#include "math.h"

using namespace math;

/** the viewer namespace contains classes dealing with display of the game */
namespace viewer {

/** the camera class encapsulated the control of the camera */
class camera{
  public:
	camera();  // default constructor
	void set(Point3 eye, Point3 look, Vector3 up); // like gluLookAt()
	void setView(CameraView cameraView);
	CameraView getView();
	Point3 getEye();
	void roll(float angle); // roll it
	void pitch(float angle); // pitch it
	void yaw(float angle); // yaw it
	void slide(float delU, float delV, float delN); // slide it
	void setShape(float vAng, float asp, float nearD, float farD);
  private:
	Point3 eye;
	Vector3 u,v,n;
	double viewAngle, aspect, nearDist, farDist; // view volume shape
	void setModelViewMatrix(); // tell OpenGL where the camera is
	CameraView view;
};

/** the view class contains methods to display the entire game */
class view{
  public:
	view();
	void initView(int *argc,char**argv);
	static void display(void);
	void drawStatus();
	void print_bitmap_string(void* font, char* s);
	int winIdSub, winIdSub2, winIdMain;
  private:
	void printProgress(float progressPercent);
	RGBpixmap pix[6];
};

}; //namespace viewer

#endif
