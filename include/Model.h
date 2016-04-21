/*!
	\class Model
	\brief 3D model
	Stores vertex positions, UV position and texture coordinates.
	Models texture and lighting can be switched on and off.
	Material can be set to the model
	Pointers used for ModelData, Material and Texture, to reduce memory usage.
	Can load/draw .obj that do not have UV points or texture coordinates.
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
	bool m_bEnableTexture;		//!< Flag that allows texture to be drawn on the model
	bool m_bEnableLight;		//!< Flag that allows light to be projected onto the model
	bool m_bModelSet;			//!< Flag that model has ModelData/vertex poitns allowing it to be drawn
	bool m_bHasMaterial;		//!< Flag that draws material onto the model affecting how it reflects light
	ModelData *m_ModelData;		//!< Pointer to model data parsed from .obj
	Material *m_Material;		//!< Points to the models material
public:
	Model();	//!<Default Constructor
	Model(string filename);						//!< Constructor sets model to be loaded
	Model(string filename, GLuint& texture);	//!< Constructor sets model to be loaded and texture to be used on model
	
	~Model();	//!< Destructor
	void setModel(ModelData &model);			//!< Set the model .obj
	void setMaterial(Material& material);		//!< Set the models material
	void enableTexture(bool b);					//!< Enable or disable textures on the model
	void enableLight(bool b);					//!< Enable or disable light on the model

	void draw();								//!< VBO draw the model
};

#endif