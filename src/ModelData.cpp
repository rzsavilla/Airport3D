#include "ModelData.h"

ModelData::ModelData() {
	m_bHasNormals = false;
	m_bHasTexture = false;
}

ModelData::ModelData(const std::vector<float> vertexTriplets, const std::vector<float> normalTriplets, const std::vector<float> texturePairs,const bool hasNormals) {
	m_vfVertexTriplets = vertexTriplets;
	m_vfVertexNormalTriplets = normalTriplets;
	m_vfVertexTexturePairs = texturePairs;
	m_bHasNormals = hasNormals;
	//m_calcSize();
	m_bHasTexture = false;
}

void ModelData::m_calcSize() {
	float minX = 9999999.f, minY =9999999.f, minZ = 9999999.f;
	float maxX = -9999999.f, maxY = -9999999.f, maxZ = -9999999.f;
	for (unsigned int i = 0; i < m_vfVertexTriplets.size(); i++) {
		//x
		if (m_vfVertexTriplets[i] < minX) {
			minX = m_vfVertexTriplets[i];
		} else if (m_vfVertexTriplets[i] > maxX) {
			maxX = m_vfVertexTriplets[i];
		}
		//y
		i++;
		if (m_vfVertexTriplets[i] < minY) {
			minY = m_vfVertexTriplets[i];
		} else if (m_vfVertexTriplets[i] > maxY) {
			maxY = m_vfVertexTriplets[i];
		}
		//z
		i++;
		if (m_vfVertexTriplets[i] < minZ) {
			minZ = m_vfVertexTriplets[i];
		} else if (m_vfVertexTriplets[i] > maxZ) {
			maxZ = m_vfVertexTriplets[i];
		}
	}
	m_vSize.setX(maxX - minX);
	m_vSize.setY(maxY - minY);
	m_vSize.setZ(maxZ - minZ);
}

void ModelData::setTexture(GLuint& texture) {
	m_Texture = &texture;
	m_bHasTexture = true;		//flag texture can be drawn
}

bool ModelData::hasNormals(){ return m_bHasNormals; }
bool ModelData::hasTexture(){ return m_bHasTexture; } 

Vector3D ModelData::getSize() { return m_vSize; };
GLuint& ModelData::getTexture() { return *m_Texture;}

std::vector<float>& const ModelData::getVertices() { return m_vfVertexTriplets;} 
std::vector<float>& const ModelData::getNormals(){ return m_vfVertexNormalTriplets; }
std::vector<float>& const ModelData::getTextureCoordinates(){ return m_vfVertexTexturePairs; }