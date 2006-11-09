/** ship constructor */
model::ship::ship(){
	readFile("SIMPBARN.3VN");
	speed = 0.05;
	position.set(0.0, 0.0, 0.0);
	direction.set(0.0, 0.0, -1.0);
}

/** ship deconstructor */
model::ship::~ship(){

}

/** health mutator method */ 
void model::ship::setHealth(int health){

}

/** health accessor method */
int model::ship::getHealth(){

}

/** score mutator method */ 
void model::ship::setScore(int score){

}

/** score accessor method */
int model::ship::getScore(){

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
	glRotated(direction.z, 0, 0, 1);
	glRotated(direction.y, 0, 1, 0);
	glRotated(direction.x, 1, 0, 0);
	glTranslatef(position.x, position.y, position.z);//Move asteroid to position in space
	
	//these three simply rotate the barn to be upright, delete for proper ship model
	glRotated(-90, 1, 0, 0);
	glRotated(90, 0, 0, 1);
	glScaled(50, 50, 50);

	//call super.draw()
	Mesh::draw();
	glPopMatrix();
}

void model::ship::doStep(float t){
	/** \todo this is where the problem is, it should be multiplying by a matrix somehow I guess 
	ie it should move a step in the given direction, hmmm */
	/*position.set(
		position.x += t * speed * direction.x,
		position.y += t * speed * direction.y,
		position.z += t * speed * direction.z
	);*/
	//move in xy axis
	position.set(
		position.x += cos(direction.x) / (speed * t),
		position.y,
		position.z += sin(direction.x) / (speed * t)
	);
}

/** \brief this function acts as an autopilot to return the ship to its default course */
void model::ship::rubberBand(){
	//factor for smooth transition
	float factor = 500;
	
	/** \todo move to better place and replace initialiser with target */
	//course to snap to
	Vector3 targetdirection;
	Vector3 targetposition;
	float targetspeed;
	targetdirection.set(0.0,0.0,-1.0);
	targetposition.set(0.0,0.0,0.0);
	targetspeed = 0.05;
	
	//reset direction
	direction.x += (targetdirection.x - direction.x)/factor;
	direction.y += (targetdirection.y - direction.y)/factor;
	direction.z += (targetdirection.z - direction.z)/factor;

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

}
