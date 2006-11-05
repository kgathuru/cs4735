#ifndef VIEW_H
#define VIEW_H

#include <GL/glut.h>

class view{
	public:
	void initView(int *argc,char**argv);
	static void display(void);
	view();
	private:
	//extern engine gameEngine;
};

#endif
