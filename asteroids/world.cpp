#include "world.h"

/**world constructor*/
model::world::world(){
	/** create asteroids */
	for (int i=0; i<INITIAL_NUM_ASTEROIDS; i++){
		asteroid astr;
		asteroids.push_back(astr);
	}
}

/**world deconstructor*/
model::world::~world(){
	//this = NULL;
}

void model::world::render(){
	/** render asteroids */
	for (asteroid_iterator iter=asteroids.begin(); iter!=asteroids.end(); iter++){
		iter->readFile("SIMPBARN.3VN");
		iter->draw();
	} 
}

/** starting point accessor method */ 
Vector3 model::world::getStartPoint(){

}

/** starting point mutator method */
void model::world::setStartPoint(Point3 v){
	
}

/** ending point accessor method */
Vector3 model::world::getEndPoint(){

}

/** ending point mutator method */
void model::world::setEndPoint(Point3 v){

}


