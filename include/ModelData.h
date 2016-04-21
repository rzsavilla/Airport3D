/*! \class ModelData
	\brief Stores parsed .obj data
	Store the vertex points, normal points and texture coordinates that have been parsed from .obj
*/

#ifndef MODELDATA_H
#define MODELDATA_H

#include <vector>
#include <SFML/glew.h>
#include "Vector3D.h"

class ModelData {
private:
	bool m_bHasNormals;			//!< Flag whether Normals can be drawn
	bool m_bHasTexture;			//!< Flag whether texture can be drawn
	Vector3D m_vSize;			//!< Models size, Width,Height,Depth (x,y,z)

	//! Finds the largest and smallest vertex point on x,y and z. Finds to the difference, which returns the WIDTH,HEIGHT and DEPTH of the object
	void m_calcSize();			
protected:
	std::vector<float> m_vfVertexTriplets;			//!< Stores parsed vertex points
	std::vector<float> m_vfVertexNormalTriplets;	//!< Stores parsed Normal points
	std::vector<float> m_vfVertexTexturePairs;		//!< Stores parsed texture coordinates
	GLuint *m_Texture;
public:
	ModelData(); //!< Default Constructor

	//! Constructor that sets parsed vertex, normal points and texture pairs.
	ModelData(const std::vector<float> vertexTriplets, const std::vector<float> normalTriplets, const std::vector<float> texturePairs, const bool hasNormals);
	
	void setTexture(GLuint& texture);					//!< Sets texture pointer

	bool hasNormals();			//!< Return flag if model has normal points									
	bool hasTexture();			//!< Return flag if model has texture coordinates								

	Vector3D getSize();									//!< Return models width, height and depth
	GLuint& getTexture();
	std::vector<float>& getVertices();					//!< Return vertex points m_vfVertexTriplets
	std::vector<float>& getNormals();					//!< Return normal points m_vfVertexNormalTriplets
	std::vector<float>& getTextureCoordinates();		//!< Return texture coordinates m_vfVertexTexturePairs
};

#endif