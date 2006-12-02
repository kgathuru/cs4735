#ifndef GAME_H
#define GAME_H

#include <GL/glut.h>

/** game engine constants */
const int INITIAL_NUM_ASTEROIDS = 31;
const int WINDOW_WIDTH = 750;
const int WINDOW_HEIGHT = 600; 
const int CAMERA_NEAR_DIST = 50; 
const int CAMERA_FAR_DIST = 20000;
const int WORLD_DEPTH = 10000; //Length of path followed by ship along the Z axis
const int WORLD_HEIGHT = 500; //Upper limit of y axis
const int WORLD_WIDTH = 500; //X axis goes from -WIDTH/2 to WIDTH/2
const int ASTEROID_MAX_SIZE = 80;
const int ASTEROID_MIN_SIZE = 30;
const int ASTEROID_SPEED = 50;
const int PANE_WIDTH = 50;
const float GAME_SPEED = 0.1; //multiplied by speed * time to move objects 
const float SHIP_SPEED = 100.0;
const int SHIP_SIZE = 50;
const float PROJECTILE_SPEED = 200;
const int SHIP_START_HEALTH = 200;
const int RELOAD_WAIT = 100;
const float PROJECTILE_SIZE = 20;

/** camera views */
enum CameraView {DEFAULT_CAM, ONBOARD_CAM};

/** game status */
enum GameStatus {GAME_START, GAME_OVER, GAME_WON, GAME_LEVEL1};

/** math constants */
static const double PI = 3.14159265358979323846264338327950288419716939937510f;

/** game colors */
const GLfloat default_emissive[] = { 0.0f, 0.0f, 0.0f, 1.0f };

const GLfloat asteroid_ambient[] = { 0.10588f, 0.058824f, 0.113725f, 1.0f}; 
const GLfloat asteroid_diffuse[] = { 0.427451f, 0.470588f, 0.541176f, 1.0f}; 
const GLfloat asteroid_specular[] = { 0.3333f, 0.3333f, 0.521569f, 1.0f}; 
const GLfloat asteroid_shininess[] = { 9.84615f };

const GLfloat ship_ambient[] = { 0.5f, 0.25f, 0.25f, 1.0f};
const GLfloat ship_specular[] = { 0.25f, 0.25f, 0.75f, 1.0f};
const GLfloat ship_diffuse[] = { 0.7, 0.0, 0.7, 1.0 };
const GLfloat ship_shininess[] = { 315.0f };

const GLfloat projectile_ambient[] = { 0.0f, 1.0f, 0.0f, 1.0f};
const GLfloat projectile_specular[] = { 0.25f, 0.25f, 0.75f, 1.0f};
const GLfloat projectile_diffuse[] = { 0.7, 0.0, 0.7, 1.0 };
const GLfloat projectile_emissive[] = { 1.0f, 1.0f, 0.0f, 1.0f };
const GLfloat projectile_shininess[] = { 315.0f };

#endif
