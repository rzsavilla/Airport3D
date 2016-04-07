#ifndef TRANSFORM_H
#define TRANSFORM_H

/*
	4,4 matrix
*/

#include "Vector3D.h"

class Transform {
private:

public:
	Transform();
	Transform(float x1, float y1, float z1,
			  float x2, float y2, float z2);
	Transform();
};

#endif