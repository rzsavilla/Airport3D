#include "Model.h"

Model::Model() {
	m_bModelSet = false;
	m_bHasMaterial = false;
	m_bEnableTexture = false;
	m_bEnableLight = false;
}

Model::~Model()  {

}

void Model::setModel(ModelData &model) {
	m_ModelData = &model;
	
	m_bModelSet = true;
	m_bEnableTexture = m_ModelData->hasNormals();
	m_bEnableLight = m_ModelData->hasTexture();
}

void Model::setMaterial(Material& material) {
	m_Material = &material;
	m_bHasMaterial = true;
}

void Model::enableTexture(bool b) { m_bEnableTexture = b; }
void Model::enableLight(bool b) { m_bEnableLight = b; }

void Model::draw() {
	//m_bHasMaterial;
	if (m_bHasMaterial) {
		glEnableClientState(GL_COLOR_MATERIAL);
		m_Material->set();
	}

	glPushMatrix();

	//Transformations
	//Translate to position
	glTranslatef(m_vPosition.getX() + m_vOrigin.getX(),m_vPosition.getY() + m_vOrigin.getY(),m_vPosition.getZ() + m_vOrigin.getZ());
	glRotatef(m_vRotation.getX(),1.0f,0.0f,0.0f);				//Rotate on origin
	glRotatef(m_vRotation.getY(),0.0f,1.0f,0.0f);
	glRotatef(m_vRotation.getZ(),0.0f,0.0f,1.0f);
	glScalef(m_vScale.getX(),m_vScale.getY(),m_vScale.getZ());	//Scale on origin
	//Move to origin
	glTranslatef(m_vPosition.getX() - m_vOrigin.getX(),m_vPosition.getY() - m_vOrigin.getY(),m_vPosition.getZ() - m_vOrigin.getZ());
	
	// Active and specify pointer to vertex array
	glEnableClientState(GL_VERTEX_ARRAY);
	vector<float>& vertices = m_ModelData->getVertices();			//Pointer to vertex array
	glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);

	if (m_bEnableLight && m_ModelData->hasNormals()) {
		glEnableClientState(GL_NORMAL_ARRAY);
		vector<float>& normals = m_ModelData->getNormals();		//Pointer to normal array
		glNormalPointer(GL_FLOAT, 0, &normals[0]);
	}

	if (m_bEnableTexture && m_ModelData->hasTexture()) {
		glEnable(GL_TEXTURE_2D);	// we are using textures
		vector<float>& textureCoordinates = m_ModelData->getTextureCoordinates();
		glBindTexture(GL_TEXTURE_2D, m_ModelData->getTexture());
		
		glEnableClientState(GL_TEXTURE_COORD_ARRAY); //glTexCoordPointer will point to an array
		glTexCoordPointer(2, GL_FLOAT, 0, &textureCoordinates[0]);
	}

	//Enable material


	//Draw shape
	glDrawArrays(GL_TRIANGLES, 0, (unsigned int)vertices.size() / 3);

	//Deactivate vertex arrays after drawing
	if (m_bEnableLight && m_ModelData->hasNormals()) {
		glDisableClientState(GL_NORMAL_ARRAY);
	}

	if (m_bEnableTexture && m_ModelData->hasTexture()) {
		// turn off the texture rendering
		glBindTexture(GL_TEXTURE_2D, NULL);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisable(GL_TEXTURE_2D);
	}
	
	//Turn off material
	

	glDisableClientState(GL_VERTEX_ARRAY);

	glPopMatrix();

	if (m_bHasMaterial) {
		glDisableClientState(GL_COLOR_MATERIAL);
	}
}