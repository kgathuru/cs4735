#include "world.h"

/**world constructor*/
model::world::world(){
	/** create asteroids */
	/** \todo change to asteroid class */ 
	for (int i=0; i<INITAL_NUM_ASTEROIDS; i++){
		object *astr = new object;
		asteroids.push_back(*astr);
	}
}

/**world deconstructor*/
model::world::~world(){
	//this = NULL;
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


