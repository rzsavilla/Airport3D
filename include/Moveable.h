#ifndef MOVEABLE_H
#define MOVEABLE_H

#include "Transformable.h"

class Moveable :public Transformable{
private:
	float m_fMass;
	float m_fForce;
public:
	void move();

	float getAcceleration();
};

#endif