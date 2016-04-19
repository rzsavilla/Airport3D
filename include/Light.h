#ifndef LIGHT_H
#define LIGHT_H

#include <SFML/glew.h>

class Light {
private:
	GLfloat lightColour[4];						//!, Stores colour values
	GLfloat noLight[4];							//!< Stores colour values
	GLfloat lightModelAmbient[4];				
	GLfloat m_position[4];						//!< Stores the lights position
	GLfloat m_rotation[3];						//!< Vector of lights current rotation on x,y and z axis
	GLenum m_LightNumber;						//!< OpenGL light number
public:
	Light(); //!< Default Constructor

	void setPostion(float x, float y, float z);							//!< Position of the light in the world
	void setRotation(float x, float y, float z);						//!< Lights orientation
	void setLightColour(float R, float G, float B, float A);			//!< Colour projected by the light
	void setNoLightColour(float R, float G, float B, float A);			//!< Colour of no light
	void setLightModelAmbient(float R, float G, float B, float A);		

	void draw();
};

#endif