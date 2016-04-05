#include "Model.h"

Model::Model() {
	m_bModelSet = false;
}

Model::~Model()  {

}

void Model::setModel(ModelData &model) {
	m_ModelData = &model;
	m_bModelSet = true;
	setOrigin(m_ModelData->getSize() / 2);	// Default origin will be centre of object
}

void Model::draw() {
	glPushMatrix();
	//Transformations
	glScalef(m_vScale.getX(),m_vScale.getY(),m_vScale.getZ());
	glTranslatef(m_vPosition.getX() + m_vOrigin.getX(),m_vPosition.getY() + m_vOrigin.getY(),m_vPosition.getZ() + m_vOrigin.getZ());
	glRotatef(m_vRotation.getX(),m_vScale.getX(),0.0f,0.0f);
	glRotatef(m_vRotation.getY(),0.0f,m_vScale.getY(),0.0f);
	glRotatef(m_vRotation.getZ(),0.0f,0.0f,m_vScale.getZ());
	glTranslatef(m_vPosition.getX() - m_vOrigin.getX(),m_vPosition.getY() - m_vOrigin.getY(),m_vPosition.getZ() - m_vOrigin.getZ());

	// Active and specify pointer to vertex array
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	vector<float>& vertices = m_ModelData->getVertices();			//Pointer to vertex array
	glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);

	if (m_ModelData->hasNormals()) {
		glEnableClientState(GL_NORMAL_ARRAY);
		vector<float>& normals = m_ModelData->getNormals();		//Pointer to normal array
		glNormalPointer(GL_FLOAT, 0, &normals[0]);
	}

	if (m_ModelData->hasTexture()) {
		glEnable(GL_TEXTURE_2D);	// we are using textures
		vector<float>& textureCoordinates = m_ModelData->getTextureCoordinates();
		glBindTexture(GL_TEXTURE_2D, m_ModelData->getTexture());
		
		glEnableClientState(GL_TEXTURE_COORD_ARRAY); //glTexCoordPointer will point to an array
		glTexCoordPointer(2, GL_FLOAT, 0, &textureCoordinates[0]);
	}

	//Draw shape
	glDrawArrays(GL_TRIANGLES, 0, (unsigned int)vertices.size() / 3);

	//Deactivate vertex arrays after drawing
	if (m_ModelData->hasNormals()) {
		glDisableClientState(GL_NORMAL_ARRAY);
	}

	if (m_ModelData->hasTexture()) {
		// turn off the texture rendering
		glBindTexture(GL_TEXTURE_2D, NULL);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisable(GL_TEXTURE_2D);
	}

	glDisableClientState(GL_VERTEX_ARRAY);

	glPopMatrix();
}