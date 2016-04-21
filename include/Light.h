/*	\class Light
	\brief OpenGL light
*/

#ifndef LIGHT_H
#define LIGHT_H

#include <SFML/glew.h>

/*
	Docs
	https://www.khronos.org/opengles/sdk/1.1/docs/man/glLight.xml
*/

class Light {
private:
	GLfloat ma_fAmbient[4];				//!< Ambient colour
	GLfloat ma_fDiffuse[4];				//!< Diffuse colour
	GLfloat ma_fSpecular[4];			//!< Specular colour
	GLfloat ma_position[4];				//!< Position of light				
	GLfloat ma_fSpotDirection[3];		//!< Direction of light
	GLfloat ma_fSpotExponent[1];		//!< Light intensity
	GLfloat ma_fSpotCutoff[1];			//!< Maximum spread of light

	GLenum m_lightNumber;				//!< OpenGL light number
public:
	Light(); //!< Default Constructor

	void setLightNum(GLenum lightNumber);						//!< Set which OpenGL light to use

	void setAmbient(float R, float G, float B, float A);		//!< Colour projected by the light
	void setDiffuse(float R, float G, float B, float A);		//!< Colour of no light
	void setSpecular(float R, float G, float B, float A);		//!< Colour of ambient light
	
	void setPosition(float x, float y, float z);				//!< Position of the light in the world
	void setSpotDirection(float x, float y, float z);			//!< Direction of light
	void setSpotExponent(float f);								//!< Light intensity
	void setSpotCutOff(float f);								//!< Light range

	float getPosX();	//!< Return x position
	float getPosY();	//!< Return y position
	float getPosZ();	//!< Return z position

	void draw();		//!< Draw the light
};

#endif