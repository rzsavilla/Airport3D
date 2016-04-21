/*! \class Transformable
	Abstract class that gives object attributes to move around in 3D Space and apply transformations to it
*/

#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include "Vector3D.h"

class Transformable {	
protected:
	Vector3D m_vPosition;			//!< Objects position x,y,z
	Vector3D m_vRotation;			//!< Objects rotation x,y,z
	Vector3D m_vOrigin;				//!< Objects origin x,y,z
	Vector3D m_vScale;				//!< Objects scale facto x,y,z Default value at 1.0f
	bool m_bUpdated;				//!< Flag, member variable has been changed
public:
	Transformable();		//!< Default Contstructor

	void move(Vector3D vector);		//!< Adds vector to current position
	void rotate(Vector3D vector);	//!< Adds vector to current rotation
	void scale(Vector3D vector);	//!< Adds vector to current scale

	void rotateX(float x);	 // Adds parameter to curent X rotation
	void rotateY(float y);	 // Adds parameter to curent Y rotation
	void rotateZ(float z);	 // Adds parameter to curent Z rotation

	void setPosition(const Vector3D newPosition);	//!< The new value to m_vPosition
	void setRotation(const Vector3D newRotation);	//!< The new value to m_vRotation
	void setOrigin(const Vector3D newOrigin);		//!< The new value to m_vOrigin
	void setScale(const Vector3D newScale);			//!< The new value to m_vScale

	void setScale(const float newScale);			//!< Set all elements of m_vScale to parameter

	void setPosition(const float x, const float y, const float z);	//!< Set the position of the object 
	void setRotation(const float x, const float y, const float z);	//!< Set Objects rotation in 3D space
	void setOrigin(const float x, const float y, const float z);	//!< Set the Objects origin 
	void setScale(const float x, const float y, const float z);		//!< Set scale of the object

	Vector3D getPosition();			//!< Return position
	Vector3D getRotation();			//!< Return rotation
	Vector3D getOrigin();			//!< Return Origin
};

#endif