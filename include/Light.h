#ifndef LIGHT_H
#define LIGHT_H

#include <SFML/glew.h>

class Light {
private:
	GLfloat lightColour[4];						//!< Stores colour values
	GLfloat noLight[4];							//!< Stores colour values
	GLfloat lightModelAmbient[4];				//!< Stores colour values ambient light	
	GLfloat m_position[4];						//!< Stores the lights position
	GLfloat m_rotation[3];						//!< Vector of lights current rotation on x,y and z axis
	GLenum m_lightNumber;						//!< OpenGL light number
public:
	Light(); //!< Default Constructor

	void setLightNum(GLenum lightNumber);

	void setPosition(float x, float y, float z);						//!< Position of the light in the world
	void setRotation(float x, float y, float z);						//!< Lights orientation
	void setLightColour(float R, float G, float B, float A);			//!< Colour projected by the light
	void setNoLightColour(float R, float G, float B, float A);			//!< Colour of no light
	void setLightModelAmbient(float R, float G, float B, float A);		//!< Colour of ambient light

	float getPosX();	//!< Return x position
	float getPosY();	//!< Return y position
	float getPosZ();	//!< Return z position
	float getRotX();	//!< Return x rotation
	float getRotY();	//!< Return y rotation
	float getRotZ();	//!< Return z rotation

	void draw();		//!< Draw the light
};

#endif