#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include "Vector3D.h"

class Transformable {	
protected:
	Vector3D m_vPosition;
	Vector3D m_vRotation;
	Vector3D m_vOrigin;
	Vector3D m_vScale;
	bool m_bUpdated;					//!< Flag, member variable has been changed
public:
	Transformable();				//!< Default Contstructor

	void move(Vector3D vector);			//!< Adds vector to current position
	void rotate(Vector3D vector);		//!< Adds vector to current rotation
	void scale(Vector3D vector);		//!< Adds vector to current scale

	void rotateX(float x);
	void rotateY(float y);
	void rotateZ(float z);

	void setPosition(const Vector3D newPosition);
	void setRotation(const Vector3D newRotation);
	void setOrigin(const Vector3D newOrigin);
	void setScale(const Vector3D newScale);

	void setScale(const float newScale);

	void setPosition(const float x, const float y, const float z);
	void setRotation(const float x, const float y, const float z);
	void setOrigin(const float x, const float y, const float z);
	void setScale(const float x, const float y, const float z);

	Vector3D getPosition();
	Vector3D getRotation();
	Vector3D getOrigin();
};

#endif