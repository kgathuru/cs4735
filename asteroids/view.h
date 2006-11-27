#ifndef VIEW_H
#define VIEW_H

#include <GL/glut.h>

namespace viewer {

class camera{
  private:
	Point3 eye;
	Vector3 u,v,n;
	double viewAngle, aspect, nearDist, farDist; // view volume shape
	void setModelViewMatrix(); // tell OpenGL where the camera is
	int cameraView;

  public:
	camera();  // default constructor
	void set(Point3 eye, Point3 look, Vector3 up); // like gluLookAt()
	void setView(int view);
	int getView();
	void roll(float angle); // roll it
	void pitch(float angle); // pitch it
	void yaw(float angle); // yaw it
	void slide(float delU, float delV, float delN); // slide it
	void setShape(float vAng, float asp, float nearD, float farD);
};

class view{


  public:
	void initView(int *argc,char**argv);
	static void display(void);
	static void subDisplay(void);
	static void subDisplay2(void);
	view();

};

};

#endif
