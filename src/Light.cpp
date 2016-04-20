#include "Light.h"
#include <iostream>

Light::Light() {
	//Default light values
	setPosition(0.0f,500.0f,0.0f);
	setSpotDirection(0.0f,0.0f,-1.0f);
	setAmbient(0.0f,0.0f,0.0f,1.0f);
	setDiffuse(1.0f,1.0f,1.0f,1.0f);
	setSpecular(1.0f, 1.0f, 1.0f, 1.0);
	setSpotExponent(0.0f);
	setSpotCutOff(180.0f);
	m_lightNumber = GL_LIGHT0;
}

void Light::setLightNum(GLenum lightNumber) {
	//Ensure enum is valid
	if (lightNumber == GL_LIGHT0 || lightNumber == GL_LIGHT1 || lightNumber == GL_LIGHT2 || lightNumber == GL_LIGHT3 || 
		lightNumber == GL_LIGHT4 || lightNumber == GL_LIGHT5 || lightNumber == GL_LIGHT6 || lightNumber == GL_LIGHT7) {
		m_lightNumber = lightNumber;
	} else {
		m_lightNumber = GL_LIGHT0;	//Default light
	}	
}

void Light::setAmbient(float R, float G, float B, float A) {
	ma_fAmbient[0] = R;
	ma_fAmbient[1] = G;
	ma_fAmbient[2] = B;
	ma_fAmbient[3] = A;
}
void Light::setDiffuse(float R, float G, float B, float A) {
	ma_fDiffuse[0] = R;
	ma_fDiffuse[1] = G;
	ma_fDiffuse[2] = B;
	ma_fDiffuse[3] = A;
}
void Light::setSpecular(float R, float G, float B, float A) {
	ma_fSpecular[0] = R;
	ma_fSpecular[1] = G;
	ma_fSpecular[2] = B;
	ma_fSpecular[3] = A;
}

void Light::setPosition(float x, float y, float z) {
	ma_position[0] = x;
	ma_position[1] = y;
	ma_position[2] = z;
	ma_position[3] = 0.5;
}
void Light::setSpotDirection(float x, float y, float z) {
	ma_fSpotDirection[0] = x;
	ma_fSpotDirection[1] = y;
	ma_fSpotDirection[2] = z;
}
void Light::setSpotExponent(float f) {
	ma_fSpotExponent[0] = f;
}
void Light::setSpotCutOff(float f) {
	ma_fSpotCutoff[0] = f;
}

float Light::getPosX(){ return ma_position[0]; }
float Light::getPosY(){ return ma_position[1]; }
float Light::getPosZ(){ return ma_position[2]; }

void Light::draw() {
	glEnable(GL_LIGHTING);
	glEnable(m_lightNumber);
	//Apply transformations
	glPushMatrix();
	glTranslatef(ma_position[0], ma_position[1], ma_position[2]);		// Move to position

	//Set Light values
	glLightfv(m_lightNumber, GL_AMBIENT, ma_fAmbient);
	glLightfv(m_lightNumber, GL_DIFFUSE, ma_fDiffuse);
	glLightfv(m_lightNumber, GL_SPECULAR, ma_fSpecular);
	glLightfv(m_lightNumber, GL_POSITION, ma_position);
	glLightfv(m_lightNumber, GL_SPOT_DIRECTION, ma_fSpotDirection);
	glLightfv(m_lightNumber, GL_SPOT_EXPONENT, ma_fSpotExponent);
	glLightfv(m_lightNumber, GL_SPOT_CUTOFF, ma_fSpotCutoff);
	
	glPopMatrix;
}