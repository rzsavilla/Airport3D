#ifndef MATERIAL_H
#define MATERIAL_H

#include <SFML/glew.h>

/*
	Docs
	https://www.opengl.org/sdk/docs/man2/xhtml/glMaterial.xml
*/

class Material {
protected:
	GLfloat ma_fAmbient[4];			//Light from all directions RGBA
	GLfloat ma_fDiffuse[4];			//Light from a source  reflectance RGBA
	GLfloat ma_fSpecular[4];		//Light from a source, light reflected(Highlights) RGBA
	GLfloat ma_fEmission[4];		// Range 1 - (-1)
	GLfloat m_fShininess;			// Single value Range 0 - 128

	const GLenum m_Shade;			// Smooth or flat shading only
public:
	Material();		//!< Default Constructor

	//Setters
	void setAmbient(float r, float g, float b, float a);
	void setDiffuse(float r, float g, float b, float a);
	void setSpecular(float r, float g, float b, float a);
	void setEmission(float r, float g, float b, float a);
	void setShininess(float f);

	void set();		//Set this as the material
};

#endif