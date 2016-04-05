#ifndef VECTOR3D_H
#define VECTOR3D_H

class Vector3D {
private:
	float m_fData[3];		//Stores x,y,z values
	void initialize();

	bool m_bHasMagnitude;	//!< Magnitude has been calculated
	float m_fMagnitude;		//!< Magnitude of the vector

	void init();			//!< Initialize flags
public:
	Vector3D();				//Default Constructor
	Vector3D(float x, float y, float z);

	void setX(float x);
	void setY(float y);
	void setZ(float z);

	float getX();
	float getY();
	float getZ();

	float angle(Vector3D& other) ;				//!< Return angle between this vector and other vector
	float dotProduct(const Vector3D& other);		//!< Returns scalar, dot product
	float magnitude();
	Vector3D unitVector();							//!< Calculate and return unit vector
	Vector3D crossProduct(const Vector3D& other);	//!< Calculate and return cross product

	Vector3D operator+ (const Vector3D& other);
	Vector3D operator- (const Vector3D& other);
	
	Vector3D operator+ (const float scalar);
	Vector3D operator- (const float scalar);
	Vector3D operator* (const float scalar);
	Vector3D operator/ (const float scalar);

};

#endif