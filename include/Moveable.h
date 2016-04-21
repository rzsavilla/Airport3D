/*
	Abstract class
	Unfinished unused used to move objects
*/

#ifndef MOVEABLE_H
#define MOVEABLE_H

#include "Transformable.h"

class Moveable :public Transformable{
private:
	float m_fMass;		//!< Mass of the object
	float m_fForce;		//!< Force being applied to the object
public:
	void setMass(float Mass);		//!< Set objects mass
	void setForce(float Force);		//!< Set force being applied to object

	void move();				//!< Update apply force to move the object
	float getAcceleration();	//!< Returns Force / Mass
};

#endif