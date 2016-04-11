#ifndef MODELDATA_H
#define MODELDATA_H

#include <vector>
#include <SFML/glew.h>
#include "Vector3D.h"

class ModelData {
private:
	bool m_bHasNormals;
	bool m_bHasTexture;
	Vector3D m_vSize;			//!< Models size, Width,Height,Depth
	void m_calcSize();			
protected:
	std::vector<float> m_vertexTriplets;
	std::vector<float> m_vertexNormalTriplets;
	std::vector<float> m_vertexTexturePairs;
	GLuint m_Texture;
public:
	ModelData(); //!< Default Constructor
	ModelData(const std::vector<float> vertexTriplets, const std::vector<float> normalTriplets, const std::vector<float> texturePairs, const bool hasNormals);
	
	void setTexture(GLuint& texture);

	bool hasNormals();
	bool hasTexture();

	Vector3D getSize();									//!< Return models width, height and depth
	GLuint& getTexture();
	std::vector<float>& getVertices();
	std::vector<float>& getNormals();
	std::vector<float>& getTextureCoordinates();
};

#endif