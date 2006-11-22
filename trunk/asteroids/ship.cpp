/** ship constructor */
model::ship::ship(){
	readFile("SIMPBARN.3VN");
	speed = 0.5;
	position.set(0.0, WORLD_HEIGHT/2, 0.0);
	direction.set(0.0, 0.0, -1.0);
	size = 100.0;
	health = SHIP_START_HEALTH;
}

/** ship deconstructor */
model::ship::~ship(){

}

/** health mutator method */ 
void model::ship::setHealth(int h){
	health = h;
}

/** health accessor method */
int model::ship::getHealth(){
	return health;
}

/** score mutator method */ 
void model::ship::setScore(int s){
	score = s;
}

/** score accessor method */
int model::ship::getScore(){
	return score;
}

/** Mutate secondary direction */
void model::ship::setSecondaryDirection(float x, float y, float z){
	secondaryDirection.set(x,y,z);
}

Vector3 model::ship::getSecondaryDirection(){
	return secondaryDirection;
}

void model::ship::moveUp(){
	secondaryDirection.y = 1.0;
	position.y = position.y + 0.1 * SHIP_SPEED * secondaryDirection.y;
}

void model::ship::moveDown(){
	secondaryDirection.y = -1.0;
	position.y = position.y + 0.1 * SHIP_SPEED * secondaryDirection.y;
}

void model::ship::moveLeft(){
	secondaryDirection.x = -1.0;
	position.x = position.x + 0.1 * SHIP_SPEED * secondaryDirection.x;
}

void model::ship::moveRight(){
	secondaryDirection.x = 1.0;
	position.x = position.x + 0.1 * SHIP_SPEED * secondaryDirection.x;
}

void model::ship::accelerate(){
	direction.z += -1.0;
	position.z = position.z + 0.1 * SHIP_SPEED * direction.z;
}

void model::ship::deccelerate(){
	direction.z += 1.0;
	position.z = position.z + 0.1 * SHIP_SPEED * direction.z;
}

/** method to control ship rotation about its own y axis */ 
void model::ship::yaw(float angle){
	direction.y += angle;
}

/** method to control ship rotation about its own x axis */
void model::ship::pitch(float angle){
	direction.x += angle;
}

void model::ship::draw(){
	glPushMatrix();
	//engage rubberband
	rubberBand();
	
	//display the ship based on position and direction vector
	//glRotated(direction.z, 0, 0, 1);
	//glRotated(direction.y, 0, 1, 0);
	//glRotated(direction.x, 1, 0, 0);
	glTranslatef(position.x, position.y, position.z);//Move asteroid to position in space
	
	//these three simply rotate the barn to be upright, delete for proper ship model
	glRotated(-90, 1, 0, 0);
	glRotated(90, 0, 0, 1);
	glScaled(100, 100, 100);

	//call super.draw()
	Mesh::draw();
	glPopMatrix();
}

void model::ship::doStep(float t){

	//Only let ship go to 0 position, not before
	position.set(
		position.x + t * speed * secondaryDirection.x,
		position.y + t * speed * secondaryDirection.y,
		position.z + t * speed * direction.z
	);
	
	//Don't let ship move out of the box
	if (position.z > 0.0){ position.z = 0.0; }
	if (position.y < 0.0){ position.y = 0.0; }
	if (position.y > WORLD_HEIGHT){ position.y = WORLD_HEIGHT; }
	if (position.x < -WORLD_WIDTH/2){ position.x = -WORLD_WIDTH/2; }
	if (position.x > WORLD_WIDTH/2){ position.x = WORLD_WIDTH/2; }

	//Check to see if ship is past finish line
	/** \todo put "you won" code? */
	if (position.z < -WORLD_DEPTH) { position.z = -WORLD_DEPTH; }
}

/** \brief this function acts as an autopilot to return the ship to its default course */
//Return ship to the middle of the box anywhere along the z axis
void model::ship::rubberBand(){
	//factor for smooth transition
	float factor = 500;
	
	/** \todo move to better place and replace initialiser with target */
	//course to snap to
	Vector3 targetdirection;
	Vector3 targetposition;
	float targetspeed;
	targetdirection.set(0.0,0.0,1.0);
	targetposition.x = 0.0;
	targetposition.y =  WORLD_HEIGHT/2;
	targetposition.z = position.z;
	targetspeed = 0.5;

	//Make secondary direction closer to (0,0,0)
	if(secondaryDirection.x != 0.0) {
		if (secondaryDirection.x < 0)
			secondaryDirection.x += 0.1;
		else
			secondaryDirection.x += -0.1;	
	}
		//Make secondary direction closer to (0,0,0)
	if(secondaryDirection.y != 0.0) {
		if(secondaryDirection.y < 0)
			secondaryDirection.y += 0.1;
		else
			secondaryDirection.y += -0.1;	
	}

	//reset direction
	secondaryDirection.z = 0.0;

	//reset position
	position.x += (targetposition.x - position.x)/factor;
	position.y += (targetposition.y - position.y)/factor;
	position.z += (targetposition.z - position.z)/factor;

	//reset speed
	speed += (targetspeed - speed)/factor;
}

/** method to fire a projectile */
/** creates a projectile object*/
void model::ship::fire(){
	projectile prot;
	prot.setSize(15);
	prot.initialize(speed * 2, direction, position);
	controller::gameEngine.theWorld.projectiles.push_back(prot);
}

//What do to when the ship dies, runs out of health
void model::ship::death(){
	//reset health
	health = SHIP_START_HEALTH;

}

//Make ship flash color when it's been hit to let player know
void model::ship::hit(){

}

