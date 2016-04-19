#include "Light.h"

Light::Light() {
	//Default light values
	setPostion(1.0f,500.0f,1.0f);
	setRotation(1.0f,1.0f,1.0f);
	setLightColour(1.0f,1.0f,1.0f,1.0f);
	setNoLightColour(0.0f,0.0f,0.0f,1.0f);
	setLightModelAmbient(0.3f, 0.3f, 0.3f, 1.0);
}

void Light::setPostion(float x, float y, float z) {
	m_position[0] = x;
	m_position[1] = y;
	m_position[2] = z;
	m_position[3] = 0.5;
}

void Light::setRotation(float x, float y, float z) {
	m_rotation[0] = x;
	m_rotation[1] = y;
	m_rotation[2] = z;
}

void Light::setLightColour(float R, float G, float B, float A) {
	lightColour[0] = R;
	lightColour[1] = G;
	lightColour[2] = B;
	lightColour[3] = A;
}
void Light::setNoLightColour(float R, float G, float B, float A) {
	noLight[0] = R;
	noLight[1] = G;
	noLight[2] = B;
	noLight[3] = A;
}
void Light::setLightModelAmbient(float R, float G, float B, float A) {
	lightModelAmbient[0] = R;
	lightModelAmbient[1] = G;
	lightModelAmbient[2] = B;
	lightModelAmbient[3] = A;
}

void Light::draw() {
	glPushMatrix();
	
	glTranslatef(m_position[0], m_position[1], m_position[2]);

	glLightfv(GL_LIGHT0, GL_POSITION, m_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColour);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightColour);
	glLightfv(GL_LIGHT0, GL_AMBIENT, noLight);			// no ambient light from the source

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightModelAmbient);	// use global ambient instead

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glPopMatrix;
}