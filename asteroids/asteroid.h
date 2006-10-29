#include "object.h"
#include "asteroid.h"
#include "math.h"

namespace model{
class asteroid: public object{
   private:
	Vector3 spin;
	
   public:
	asteroid(); 		// constructor
	void setSpin(float Sx, float Sy, float Sz);	//Set the spin in degrees
	Vector3 getSpin();	//Return spin
};
};