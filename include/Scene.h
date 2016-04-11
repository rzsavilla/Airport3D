#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>

#include "ModelReader.h"
#include "ModelData.h"
#include "Model.h"
#include "TextureLoader.h"
#include "Drawable.h"
#include "Camera.h"
#include "Light.h"

class Scene: public Drawable {
private:
	bool m_bModelDataLoaded;
	bool m_bTexturesLoaded;
private:
	std::vector<std::pair<int,GLuint>> m_viTextures;	
	std::vector<std::pair<int,ModelData>> m_vModelData;
	std::vector<std::pair<int,Model>> m_vModels;
	std::string m_sFilename;				//!< File location of .txt file
	GLuint& getTexture(int id);
	ModelData& getModelData(int id);
	Light light;
private:
	unsigned int m_uiCamera;				//!< Index for camera to draw/use
	std::vector<std::pair<int,Camera>> m_vCamera;			//!< Store Camera
private:
	std::string m_sSceneBaseDir;
	std::string m_sModelBaseDir;
	std::string m_sTextureBaseDir;
	void loadModelData(istringstream& iss);
	void loadTexture(istringstream& iss);
	void loadCamera(istringstream& iss);
	void loadModel(istringstream& iss);
	void readQuotes(istringstream& iss, int& value);
	void readQuotes(istringstream& iss, float& value);
	void readQuotes(istringstream& iss, std::string& value);
public:
	Scene();
	Scene(std::string filename);

	/*! Loads a scene from a file, 
		including models
	*/
	void loadScene(std::string filename);
	void reset();				//!< Reset the scene, resets position/orientation of all models
	void update(float h);
	void draw();				//Draw models

	Camera* getCamera();
};

#endif