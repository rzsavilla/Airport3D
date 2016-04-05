#include "ModelData.h"

ModelData::ModelData() {
	m_bHasNormals = false;
	m_bHasTexture = false;
}

ModelData::ModelData(std::vector<float> vertexTriplets, std::vector<float> normalTriplets, std::vector<float> texturePairs, bool hasNormals) {
	m_vertexTriplets = vertexTriplets;
	m_vertexNormalTriplets = normalTriplets;
	m_vertexTexturePairs = texturePairs;
	m_bHasNormals = hasNormals;
	m_calcSize();
	m_bHasTexture = false;
}

void ModelData::m_calcSize() {
	float minX = 9999999.f, minY =9999999.f, minZ = 9999999.f;
	float maxX = -9999999.f, maxY = -9999999.f, maxZ = -9999999.f;
	for (unsigned int i = 0; i < m_vertexTriplets.size(); i++) {
		//x
		if (m_vertexTriplets[i] < minX) {
			minX = m_vertexTriplets[i];
		} else if (m_vertexTriplets[i] > maxX) {
			maxX = m_vertexTriplets[i];
		}
		//y
		i++;
		if (m_vertexTriplets[i] < minY) {
			minY = m_vertexTriplets[i];
		} else if (m_vertexTriplets[i] > maxY) {
			maxY = m_vertexTriplets[i];
		}
		//z
		i++;
		if (m_vertexTriplets[i] < minZ) {
			minZ = m_vertexTriplets[i];
		} else if (m_vertexTriplets[i] > maxZ) {
			maxZ = m_vertexTriplets[i];
		}
	}
	m_vSize.setX(maxX - minX);
	m_vSize.setY(maxY - minY);
	m_vSize.setZ(maxZ - minZ);
}

void ModelData::setTexture(GLuint& texture) {
	m_Texture = texture;
	m_bHasTexture = true;
}

bool ModelData::hasNormals(){ return m_bHasNormals; }
bool ModelData::hasTexture(){ return m_bHasTexture; } 

Vector3D ModelData::getSize() { return m_vSize; };
GLuint& ModelData::getTexture() { return m_Texture;}

std::vector<float>& ModelData::getVertices() { return m_vertexTriplets;}
std::vector<float>& ModelData::getNormals(){ return m_vertexNormalTriplets; }
std::vector<float>& ModelData::getTextureCoordinates(){ return m_vertexTexturePairs; }