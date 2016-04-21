/*!
	\class Model
	\brief 3D model
	Stores vertex positions, UV position and texture coordinates.
	Models texture and lighting can be switched on and off.
	Material can be set to the model
	Pointers used for ModelData, Material and Texture, to reduce memory usage.
*/

#ifndef MODEL_H
#define MODEL_H

#include "TextureLoader.h"
#include "ModelData.h"
#include "Drawable.h"

#include "Vector3D.h"
#include "Transformable.h"
#include "Material.h"

class Model: public Drawable, public Transformable{
private:
	bool m_bEnableTexture;
	bool m_bEnableLight;
	bool m_bModelSet;			
	bool m_bHasMaterial;
	ModelData *m_ModelData; 
	Material *m_Material;
public:
	Model();	//!<Default Constructor
	Model(string filename);						//!< Constructor sets model to be loaded
	Model(string filename, GLuint& texture);	//!< Constructor sets model to be loaded and texture to be used on model
	
	~Model();	//!< Destructor
	void setModel(ModelData &model);
	void setMaterial(Material& material);
	void enableTexture(bool b);
	void enableLight(bool b);

	void draw();
};

#endif