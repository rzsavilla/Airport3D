#include "Material.h"

Material::Material()
	: m_Shade(GL_SMOOTH)
{
	//Default values
	setAmbient(1.0f,1.0f,1.0f,1.0f);
	setDiffuse(0.8f,0.8f,0.8f,1.0f);
	setSpecular(0.0f,0.0f,0.0f,1.0f);
	setEmission(0.0f,0.0f,0.0f,1.0f);
	setShininess(0.0f);
}

void Material::setAmbient(float r, float g, float b, float a) {
	ma_fAmbient[0] = r;
	ma_fAmbient[1] = g;
	ma_fAmbient[2] = b;
	ma_fAmbient[3] = a;
}
void Material::setDiffuse(float r, float g, float b, float a) {
	ma_fDiffuse[0] = r;
	ma_fDiffuse[1] = g;
	ma_fDiffuse[2] = b;
	ma_fDiffuse[3] = a;
}
void Material::setSpecular(float r, float g, float b, float a) {
	ma_fSpecular[0] = r;
	ma_fSpecular[1] = g;
	ma_fSpecular[2] = b;
	ma_fSpecular[3] = a;
}
void Material::setEmission(float r, float g, float b, float a) {
	ma_fEmission[0] = r;
	ma_fEmission[1] = g;
	ma_fEmission[2] = b;
	ma_fEmission[3] = a;
}
void Material::setShininess(float f) {
	m_fShininess = f;
}

void Material::set() {
	glShadeModel(m_Shade);
	glMaterialfv(GL_FRONT,GL_AMBIENT, ma_fAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ma_fDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, ma_fSpecular);
	//glMaterialfv(GL_FRONT, GL_EMISSION, ma_fEmission);
	glMaterialf(GL_FRONT, GL_SHININESS, m_fShininess);
}