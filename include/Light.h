#ifndef LIGHT_H
#define LIGHT_H

#include <SFML/glew.h>

class Light {
private:
	GLfloat lightColour[4];
	GLfloat noLight[4];
	GLfloat lightModelAmbient[4];
	GLfloat m_position[4];
	GLfloat m_rotation[3];
public:
	Light(); //!< Default Constructor

	void setPostion(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void setLightColour(float R, float G, float B, float A);
	void setNoLightColour(float R, float G, float B, float A);
	void setLightModelAmbient(float R, float G, float B, float A);

	void draw();
};

#endif