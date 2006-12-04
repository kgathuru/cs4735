#ifndef GAME_H
#define GAME_H

#include <GL/glut.h>

// game engine constants

const int INITIAL_NUM_ASTEROIDS = 50; ///< initial number of asteroids
const int WINDOW_WIDTH = 750; ///< width of main window
const int WINDOW_HEIGHT = 600; ///< high of main window
const int CAMERA_NEAR_DIST = 50; ///< near distance for default camera
const int CAMERA_FAR_DIST = 20000; ///< far distance for default camera
const int WORLD_DEPTH = 10000; ///< Length of path followed by ship along the Z axis
const int WORLD_HEIGHT = 500; ///< Upper limit of y axis
const int WORLD_WIDTH = 500; ///< X axis goes from -WIDTH/2 to WIDTH/2
const int ASTEROID_MAX_SIZE = 80; ///< maximum size of asteroids 
const int ASTEROID_MIN_SIZE = 30; ///< minimum size of asteroids
const int ASTEROID_SPEED = 75; ///< default initial speed of asteroids
const float GAME_SPEED = 0.1; ///< multiplied by speed * time to move objects 
const float SHIP_SPEED = 100.0; ///< default speed of ship
const int SHIP_SIZE = 50; ///< default size of ship
const float PROJECTILE_SPEED = 200; ///< defalt speed of projectiles
const int SHIP_START_HEALTH = 250; ///< starting health
const int RELOAD_WAIT = 100; ///< time taken to reload guns 
const float PROJECTILE_SIZE = 20; ///< default projectile size

/** camera views */
enum CameraView {
	START_CAM, ///< camera view from beinning of world 
	ONBOARD_CAM, ///< camera that is connected to the ship 
	EXTERNAL_CAM ///< camera viewing ship from left for testing purposes
};

/** game status */
enum GameStatus {
	GAME_START, ///< dislay startup screen
	GAME_OVER, ///< display game over screen
	GAME_WON, ///< display you won screen
	GAME_LEVEL1 ///< display level1
};

/** value of PI */  
static const double PI = 3.14159265358979323846264338327950288419716939937510f;

// game colors

const GLfloat default_emissive[] = { 0.0f, 0.0f, 0.0f, 1.0f }; /// default material emissive color

const GLfloat asteroid_ambient[] = { 0.10588f, 0.058824f, 0.113725f, 1.0f}; ///< asteroid ambient color
const GLfloat asteroid_diffuse[] = { 0.427451f, 0.470588f, 0.541176f, 1.0f}; ///< asteroid diffuse color
const GLfloat asteroid_specular[] = { 0.3333f, 0.3333f, 0.521569f, 1.0f}; ///< asteroid specular color
const GLfloat asteroid_shininess[] = { 9.84615f }; ///< asteroid shininess value

const GLfloat ship_ambient[] = { 0.5f, 0.25f, 0.25f, 1.0f}; ///< ship ambient color
const GLfloat ship_specular[] = { 0.25f, 0.25f, 0.75f, 1.0f}; ///< ship specular color
const GLfloat ship_diffuse[] = { 0.7, 0.0, 0.7, 1.0 }; ///< ship diffuse color
const GLfloat ship_shininess[] = { 315.0f }; ///< ship specular value

const GLfloat projectile_ambient[] = { 0.0f, 1.0f, 0.0f, 1.0f}; ///< projectile ambient color
const GLfloat projectile_specular[] = { 0.25f, 0.25f, 0.75f, 1.0f}; ///<projectile specular color
const GLfloat projectile_diffuse[] = { 0.7, 0.0, 0.7, 1.0 }; ///< projectile diffuse color
const GLfloat projectile_emissive[] = { 1.0f, 1.0f, 0.0f, 1.0f }; ///< projectile emissive color
const GLfloat projectile_shininess[] = { 315.0f }; ///< projectile shininess value

#endif
