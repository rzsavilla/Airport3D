/*!	\file Scene.h
	\class Scene
	\brief Loads, stores, updates and draws objects into the world.
*/

#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>

#include "Drawable.h"
#include "ModelReader.h"
#include "ModelData.h"
#include "Model.h"
#include "TextureLoader.h"
#include "Camera.h"
#include "Light.h"

class Scene: public Drawable {
private:
	bool m_bModelDataLoaded;			//!< Flag to check that all model data have been loaded
	bool m_bTexturesLoaded;				//!< Flag to check that all textures have been loaded
private:
	ModelReader m_ModelReader;
	std::vector<std::pair<int,GLuint>> m_viTextures;		//!< Stores object id and texture data
	std::vector<std::pair<int,ModelData>> m_vModelData;		//!< Stores object id and model data object
	std::vector<std::pair<int,Material>> m_vMaterial;		//!< Stores object id and Material object
	std::vector<std::pair<int,Model>> m_vModels;			//!< Stores object id and model object
	std::vector<std::pair<int,Light>> m_vLights;			//!< Stores object id and light object
	
	std::string m_sFilename;				//!< File location of .txt file
	GLuint& getTexture(int id);				//!< Returns texture
	ModelData& getModelData(int id);		//!< Return model data
	Material& getMaterial(int id);			//!< Return material
private:
	unsigned int m_uiCamera;								//!< Index for camera to draw/use
	std::vector<std::pair<int,Camera>> m_vCamera;			//!< Store Camera
private:
	//Scene parser
	const string k_sComment;

	std::string m_sSceneBaseDir;								//!< Location of scene files
	std::string m_sModelBaseDir;								//!< Location of model files
	std::string m_sTextureBaseDir;								//!< Location of texture files
	void loadModelData(istringstream& iss);						//!< Read model data and store into vector
	void loadTexture(istringstream& iss);						//!< Read texture and store into vector
	void loadMaterial(istringstream& iss);						//!< Read material and store into vector
	void loadLight(istringstream& iss);							//!< Read light and store into vector
	void loadCamera(istringstream& iss);						//!< Read camera and store into vector
	void loadModel(istringstream& iss);							//!< Read model and store into vector
	void readQuotes(istringstream& iss, int& value);			//!< Read and store in value into int
	void readQuotes(istringstream& iss, float& value);			//!< Read and store float value into float
	void readQuotes(istringstream& iss, std::string& value);	//!< Read and store string value into string
	void removeReturn(istringstream& iss);						//!< Read away "\n"
	void removeTab(istringstream& iss);							//!< Read away \t"
public:
	Scene();							//!< Default constructor
	Scene(std::string filename);		//!< Construcor loads scene

	/*! Loads a scene from a file, 
		including models
	*/
	void loadScene(std::string filename);	//!< Will open and parse scene file \param filename Location and name of scene file
	void reset();							//!< Reset the scene, resets position/orientation of all models
	void update(float h);					//!< update all scene objects \param h Timestep used on moving objects
	void draw();							//!< Draw all scene objects

	Camera* getCamera();					//!< Return current camera being drawn
};

#endif