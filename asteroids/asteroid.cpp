#include "object.h"
#include "math.h"

asteroid::asteroid()
{
	//Set speed to all be the same
	speed = 10.0;
	//Set direction to all be the same

	//Set the spin to all be zero by default
	spin.set(0.0,0.0,0.0);
}


void setSpin(float Sx, float Sy, float Sz)
{
	spin.set(Sx,Sy,Sz);
}

Vector3 getSpin()
{
	return spin;
}