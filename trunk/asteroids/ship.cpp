
/** ship constructor */
model::ship::ship(){
	//readFile("SIMPBARN.3VN");
	speed = 0.5;
	position.set(0.0, WORLD_HEIGHT/2, 0.0);
	direction.set(0.0, 0.0, -1.0);
	size = SHIP_SIZE;
	health = SHIP_START_HEALTH;
	reload = 0;
	score = 0;
	damage = 0;
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

/**  reload time accessor method */
void model::ship::setReload(int r){
	reload = r;
}

/** reload mutator method */
int model::ship::getReload(){
	return reload;
}

/** Mutate secondary direction */
void model::ship::setSecondaryDirection(float x, float y, float z){
	secondaryDirection.set(x,y,z);
}

/** access secondary direction */
Vector3 model::ship::getSecondaryDirection(){
	return secondaryDirection;
}

/** moves the ship up */
void model::ship::moveUp(){
	secondaryDirection.y = 1.0;
	position.y = position.y + 0.1 * SHIP_SPEED * secondaryDirection.y;
}

/** moves the ship down */
void model::ship::moveDown(){
	secondaryDirection.y = -1.0;
	position.y = position.y + 0.1 * SHIP_SPEED * secondaryDirection.y;
}

/** moves the ship left */
void model::ship::moveLeft(){
	secondaryDirection.x = -1.0;
	position.x = position.x + 0.1 * SHIP_SPEED * secondaryDirection.x;
}

/** moves the ship right */
void model::ship::moveRight(){
	secondaryDirection.x = 1.0;
	position.x = position.x + 0.1 * SHIP_SPEED * secondaryDirection.x;
}

/** makes the ship go faster */
void model::ship::accelerate(){
	direction.z += -1.0;
	position.z = position.z + 0.1 * SHIP_SPEED * direction.z;
}

/** makes the ship go slower */
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

/** override parent draw method */
void model::ship::draw(){
	glPushMatrix();

	//engage rubberband
	rubberBand();
	
	//place in correct position
	glTranslatef(position.x , position.y +15, position.z -10);
	glRotated(30, 1, 0, 0);
	glRotated(90, 0, 0,1);
	glRotated(-190, 0,1,0);
	glScaled(size, size, size);

	//draw ship
	rocketShip();

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

	if(reload > 0)
		reload--;

	//Check to see if ship is past finish line
	if (position.z < -WORLD_DEPTH) { position.z = -WORLD_DEPTH; }
}

/** this function acts as an autopilot to return the ship to its default course */
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
	//targetspeed = 0.5;
	targetspeed = 10;

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

/** ship fires, creates a projectile object*/
void model::ship::fire(){
	projectile prot;
	prot.setSize(15);
	prot.initialize(speed * 2, direction, position);
	controller::gameEngine.theWorld.projectiles.push_back(prot);
}

/** What do to when the ship dies, runs out of health */
void model::ship::death(){
	//reset health
	//Reset position back to start
// 	position.set(0.0, WORLD_HEIGHT/2, 0.0);
// 	direction.set(0.0, 0.0, -1.0);
// 	health = SHIP_START_HEALTH;
// 	score = 0;
}

/** Make ship flash color when it's been hit to let player know */
void model::ship::hit(){
	//cout << "Serenity hit\n";
	damage += 50;
}

/** draws a rocket ship model*/
void model::ship::rocketShip(){

	GLUquadricObj*	qobj;
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	qobj = gluNewQuadric();	
	gluQuadricDrawStyle(qobj, GLU_FILL);
        gluQuadricNormals(qobj, GLU_SMOOTH);
        gluQuadricTexture(qobj, GL_TRUE);
 
	glPushMatrix();
	//Front Cone
	glBindTexture(GL_TEXTURE_2D, 2005);   // choose the texture to use.
	gluCylinder(qobj,0.5,0.01, 1, 10, 10);
	glPopMatrix();

	//Cylinder body
	glPushMatrix();
	glTranslated(0.0, 0.0, -1.0);
	glColor3f(0,1,0);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	if (damage > 0){
 		glBindTexture(GL_TEXTURE_2D, 2005);   // choose the texture to use.
		damage--;
	} else { 
 		glBindTexture(GL_TEXTURE_2D, 2004);   // choose the texture to use.
	}
	gluCylinder(qobj, 0.5, 0.5, 1.0, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, 0.0, -1.0);
	gluDisk(qobj, 0, 0.5, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -0.5, -1.0);
	//Back Cone
	glBindTexture(GL_TEXTURE_2D, 2005);   // choose the texture to use.
	gluCylinder(qobj, 0.4, 0.01, 0.4, 5, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0, 0.5, -1.0);
	//Back Cone
	gluCylinder(qobj, 0.4, 0.01, 0.4, 5, 5);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	

	//DOESN'T WORK????
	//Crosshair
	glPushMatrix();
	glTranslated(0.5, 0.5, 10.0);
	glRotatef(90,1,0,0);
	glBindTexture(GL_TEXTURE_2D, 2004);   // choose the texture to use.
	gluCylinder(qobj, 0.4, 0.01, 0.4, 5, 5);
	glPopMatrix();

	/*
	//Draw crosshair
	glDisable(GL_LIGHTING);	//Allow colors to be drawn regardless of light
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(2);
	glBegin(GL_LINES);
		glVertex3f(-50, 0, -100);
		glVertex3f(50, 0, -100);
		glVertex3f(0, -50, -100);
		glVertex3f(0, 50, -100);
	glEnd();
	glEnable(GL_LIGHTING);
	*/
}

