/** ship constructor */
model::ship::ship(){
	readFile("SIMPBARN.3VN");
	speed = 0.05;
	position.set(0.0, 0.0, 0.0);
	direction.set(0.0,0.0,0.0);
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
	direction.x += angle;
}

/** method to control ship rotation about its own x axis */
void model::ship::pitch(float angle){
	direction.z += angle;
}

void model::ship::draw(){
	glPushMatrix();

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

void model::ship:: doStep(float t){
	position.set(
		position.x += t * speed * direction.x,
		position.y += t * speed * direction.y,
		position.z += t * speed * direction.z
	);
}

/** method to fire a projectile */
/** creates a projectile object*/
void model::ship::fire(){

}
