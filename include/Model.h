#ifndef MODEL_H
#define MODEL_H

#include "TextureLoader.h"
#include "ModelData.h"
#include "Drawable.h"

#include "Vector3D.h"
#include "Transformable.h"

class Model: public Drawable, public Transformable {
private:
	ModelData *m_ModelData; 
	bool m_bModelSet;
public:
	Model();	//!<Default Constructor
	Model(string filename);						//!< Constructor sets model to be loaded
	Model(string filename, GLuint& texture);	//!< Constructor sets model to be loaded and texture to be used on model
	
	~Model();	//!< Destructor
	void setModel(ModelData &model);

	void draw();
};

#endif