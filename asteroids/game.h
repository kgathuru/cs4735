#ifndef GAME_H
#define GAME_H

#include <GL/glut.h>

/** game engine constants */
const int INITIAL_NUM_ASTEROIDS = 30;
const int WINDOW_WIDTH = 750;
const int WINDOW_HEIGHT = 600; 
const int WORLD_DEPTH = 1000; //Length of path followed by ship along the Z axis
const int WORLD_HEIGHT = 500; //Upper limit of y axis
const int WORLD_WIDTH = 500; //X axis goes from -WIDTH to WIDTH
const int ASTEROID_MAX_SIZE = 40;
const int ASTEROID_MIN_SIZE = 10;
const int ASTEROID_SPEED = 25;
const int PANE_WIDTH = 50;
const float GAME_SPEED = 0.1; //multiplied by speed * time to move objects 

/** math constants */
static const double PI = 3.14159265358979323846264338327950288419716939937510f;

/** game colors, should we move this? */
const GLfloat asteroid_ambient[] = { 0.5f, 0.25f, 0.25f, 1.0f};
const GLfloat asteroid_specular[] = { 0.25f, 0.25f, 0.75f, 1.0f};
const GLfloat asteroid_diffuse[] = { 0.7, 0.4, 0.4, 1.0 };
const GLfloat asteroid_shininess[] = { 125.0f };	

const GLfloat ship_ambient[] = { 0.5f, 0.25f, 0.25f, 1.0f};
const GLfloat ship_specular[] = { 0.25f, 0.25f, 0.75f, 1.0f};
const GLfloat ship_diffuse[] = { 0.7, 0.0, 0.7, 1.0 };
const GLfloat ship_shininess[] = { 315.0f };

#endif
