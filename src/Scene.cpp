#include "Scene.h"

Scene::Scene()
	: k_sComment("#")
{
	//Set default values
	m_sSceneBaseDir = "scene/";
	m_sModelBaseDir = "models/";
	m_sTextureBaseDir = "images/";
	m_uiCamera = 0;
}

Scene::Scene(std::string filename) 
	: k_sComment("#")
{
	//Set default values
	m_sSceneBaseDir = "scene/";
	m_sModelBaseDir = "models/";
	m_sTextureBaseDir = "images/";
	m_uiCamera = 0;

	loadScene(filename);	//load scene
}

void Scene::loadScene(std::string filename) {
	sf::Clock elapsed;
	elapsed.restart();
	m_sFilename = filename;
	std::cout << "Loading Scene: " << filename << std::endl;
	std::fstream sceneFile(m_sSceneBaseDir+filename,std::ios_base::in);

	if (!sceneFile.is_open()) {
		std::cerr << "Scene File: " << filename << " not found.";
		DebugBreak();
		throw std::invalid_argument("File not found");
		return;		//Exit function
	}
	std::string sLine = "";
	std::string sToken = "";
	while (getline(sceneFile, sLine, '\>')) {		//Read everything withing the ('\>')
		istringstream iss(sLine);
		sToken = "";
		
		iss >> sToken;
		if (sToken == k_sComment) {
			continue;					//Ignore comment comment end is '\>'
		}
		else if (sToken == "<texture") {
			//std::cout << "Texture found\n";
			loadTexture(iss);
		} 
		else if (sToken == "<material") {
			//std::cout << "Material found\n";
			loadMaterial(iss);
		}
		else if (sToken == "<modeldata") {
			//std::cout << "ModelData found\n";
			loadModelData(iss);
		}
		else if (sToken == "<light") {
			//std::cout << "light found\n";
			loadLight(iss);
		}
		else if (sToken == "<camera") {
			loadCamera(iss);
		}
		else if (sToken == "<model") {
			//std::cout << "model found\n";
			loadModel(iss);
		}
		std::cout << "\t" << elapsed.getElapsedTime().asSeconds() << std::endl;
		elapsed.restart();
	}

	sceneFile.close();			//Close the file
}

void Scene::loadTexture(istringstream& iss) {
	int id = 0;
	std::string sAttribute;
	std::string sFilename = "";

	while (!iss.eof()) {	//While not end of line
		removeReturn(iss);
		removeTab(iss);
		getline(iss,sAttribute, '=');
		if (sAttribute == "id") {
			readQuotes(iss, id);
		}
		else if (sAttribute == "filename") {
			readQuotes(iss,sFilename);
		}
	}

	std::cout << "Loading: " << sFilename << "\t";

	if (!sFilename.empty()) {
		TextureLoader loader;
		std::pair<int,GLuint> data;
		data.first = id;
		loader.LoadBMP(m_sTextureBaseDir+sFilename,data.second);
		m_viTextures.push_back(data);
	}
}

void Scene::loadMaterial(istringstream& iss) {
	int id = 0;
	std::string sAttribute;
	std::string sFilename = "";

	GLfloat fAmbient[4] = { 1.0f,1.0f,1.0f,1.0f };	
	GLfloat fDiffuse[4] = { 0.0f,0.0f,0.0f,1.0f };
	GLfloat fSpecular[4] = { 0.0f,0.0f,0.0f,1.0f };
	GLfloat fEmission[4] = { 0.0f,0.0f,0.0f,1.0f };
	GLfloat fShininess = 0.0f;
	Material material;

	while (!iss.eof()) {	//While not end of line
		removeReturn(iss);
		removeTab(iss);
		getline(iss,sAttribute, '=');
		if (sAttribute == "id") {
			readQuotes(iss, id);
		} else if (sAttribute == "filename") {
			readQuotes(iss, sFilename);
		}
		//Read material properties
		else if (sAttribute == "ambientR") { readQuotes(iss, fAmbient[0]); }
		else if (sAttribute == "ambientG") { readQuotes(iss, fAmbient[1]); }
		else if (sAttribute == "ambientB") { readQuotes(iss, fAmbient[2]); }
		else if (sAttribute == "ambientA") { readQuotes(iss, fAmbient[3]); }

		else if (sAttribute == "diffuseR") { readQuotes(iss, fDiffuse[0]); }
		else if (sAttribute == "diffuseG") { readQuotes(iss, fDiffuse[1]); }
		else if (sAttribute == "diffuseB") { readQuotes(iss, fDiffuse[2]); }
		else if (sAttribute == "diffuseA") { readQuotes(iss, fDiffuse[3]); }

		else if (sAttribute == "specularR") { readQuotes(iss, fSpecular[0]); }
		else if (sAttribute == "specularG") { readQuotes(iss, fSpecular[1]); }
		else if (sAttribute == "specularB") { readQuotes(iss, fSpecular[2]); }
		else if (sAttribute == "specularA") { readQuotes(iss, fSpecular[3]); }

		else if (sAttribute == "emissionR") { readQuotes(iss, fEmission[0]); }
		else if (sAttribute == "emissionG") { readQuotes(iss, fEmission[1]); }
		else if (sAttribute == "emissionB") { readQuotes(iss, fEmission[2]); }
		else if (sAttribute == "emissionA") { readQuotes(iss, fEmission[3]); }

		else if (sAttribute == "shininess") { readQuotes(iss, fShininess); }
	}
	//Set material properties
	material.setAmbient(fAmbient[0], fAmbient[1], fAmbient[2], fAmbient[3]);
	material.setDiffuse(fDiffuse[0], fDiffuse[1], fDiffuse[2], fDiffuse[3]);
	material.setSpecular(fSpecular[0], fSpecular[1], fSpecular[2], fSpecular[3]);
	material.setEmission(fEmission[0], fEmission[1], fEmission[2], fEmission[3]);
	material.setShininess(fShininess);

	//Add Matrial into vector
	m_vMaterial.push_back(std::pair<int,Material>(id, material));
}

void Scene::loadModelData(istringstream& iss) {
	int id = 0;
	int iTextureID = -1;
	std::string sAttribute;
	std::string sFilename = "";
	while (!iss.eof()) {
		removeReturn(iss);
		removeTab(iss);
		getline(iss,sAttribute, '=');
		
		if (sAttribute == "id") {
			readQuotes(iss, id);				//Read attribute value
		}
		else if (sAttribute == "filename") {
			readQuotes(iss,sFilename);			//Read attribute value
		}
		else if (sAttribute == "textureID") {
			readQuotes(iss,iTextureID);
		}
	}

	std::cout << "Loading: " << sFilename << "\t";

	if (!sFilename.empty()) {	
		std::pair<int,ModelData> data(id,m_ModelReader.ReadModelObjData(m_sModelBaseDir+sFilename));	//set Model Id, read obj
		if (iTextureID >= 0) { data.second.setTexture(getTexture(iTextureID)); }						//Set Texture, texture ID Must be greater than or equal to 0
		m_vModelData.push_back(data);																	//Add model to vector
		std::cout << "Loaded\t";
	} 
	else {
		std::cout << "Failed\t";
	}
}

void Scene::loadLight(istringstream& iss) {
	std::string sAttribute;
	std::string sFilename = "";
	int id = 0;
	//Default values
	GLfloat a_fAmbient[4] = { 0.0f, 0.0f, 0.0f, 1.0f};	
	GLfloat a_fSpecular[4] = { 1.0f, 1.0f, 1.0f, 1.0f};			//White light			
	GLfloat a_fDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f};				
	GLfloat a_fPosition[4] = { 0.0f, 0.0f, 0.0f, 0.0f};			
	GLfloat a_fSpotDirection[3]  = { 0.0f, 0.0f, -1.0f};
	GLfloat a_fSpotExponent[1] = { 0.0f };
	GLfloat a_fSpotCutOff[1] = { 180.0f };
	
	Light light;

	while (!iss.eof()) {
		removeReturn(iss);
		removeTab(iss);
		getline(iss,sAttribute, '=');
		if (sAttribute == "id") {
			readQuotes(iss, id);				//Read attribute value
		} else if (sAttribute == "filename") {
			readQuotes(iss,sFilename);
		}
		else if (sAttribute == "lightnumber") {
			int i;
			GLenum iLightNumber = GL_LIGHT0;	//Default
			readQuotes(iss,i);
			switch (i)
			{
			case 0:
				iLightNumber = GL_LIGHT0;
				break;
			case 1:
				iLightNumber = GL_LIGHT1;
				break;
			case 2:
				iLightNumber = GL_LIGHT2;
				break;
			case 3:
				iLightNumber = GL_LIGHT3;
				break;
			case 4:
				iLightNumber = GL_LIGHT4;
				break;
			case 5:
				iLightNumber = GL_LIGHT5;
				break;
			case 6:
				iLightNumber = GL_LIGHT6;
				break;
			case 7:
				iLightNumber = GL_LIGHT7;
				break;
			default:
				break;
			}
			light.setLightNum(iLightNumber);
		}
		// Read Light Colour
		else if (sAttribute == "ambientR") { readQuotes(iss,a_fAmbient[0]); }
		else if (sAttribute == "ambientG") { readQuotes(iss,a_fAmbient[1]); }
		else if (sAttribute == "ambientB") { readQuotes(iss,a_fAmbient[2]); }
		else if (sAttribute == "ambientA") { readQuotes(iss,a_fAmbient[3]); }
		// Read No Light colour
		else if (sAttribute == "diffuseR") { readQuotes(iss,a_fDiffuse[0]); }
		else if (sAttribute == "diffuseG") { readQuotes(iss,a_fDiffuse[1]); }
		else if (sAttribute == "diffuseB") { readQuotes(iss,a_fDiffuse[2]); }
		else if (sAttribute == "diffuseA") { readQuotes(iss,a_fDiffuse[3]); }
		// Read Ambient light
		else if (sAttribute == "specularR") { readQuotes(iss,a_fAmbient[0]); }
		else if (sAttribute == "specularG") { readQuotes(iss,a_fAmbient[1]); }
		else if (sAttribute == "specularB") { readQuotes(iss,a_fAmbient[2]); }
		else if (sAttribute == "specularA") { readQuotes(iss,a_fAmbient[3]); }
		// Read Position
		else if (sAttribute == "posx") { readQuotes(iss,a_fPosition[0]); }
		else if (sAttribute == "posy") { readQuotes(iss,a_fPosition[1]); }
		else if (sAttribute == "posz") { readQuotes(iss,a_fPosition[2]); }
		else if (sAttribute == "posw") { readQuotes(iss,a_fPosition[3]); }
		// Read Rotation
		else if (sAttribute == "dirx") { readQuotes(iss,a_fSpotDirection[0]); }
		else if (sAttribute == "diry") { readQuotes(iss,a_fSpotDirection[1]); }
		else if (sAttribute == "dirz") { readQuotes(iss,a_fSpotDirection[2]); }
		// Read Exponent/intensity
		else if (sAttribute == "exp") { readQuotes(iss,a_fSpotExponent[0]); }
		else if (sAttribute == "cutoff") { readQuotes(iss,a_fSpotCutOff[0]); }
	}
	
	//Set light properties
	light.setAmbient(a_fAmbient[0], a_fAmbient[1], a_fAmbient[2] , a_fAmbient[3]);
	light.setDiffuse(a_fDiffuse[0], a_fDiffuse[1], a_fDiffuse[2] , a_fDiffuse[3]);
	light.setSpecular(a_fSpecular[0], a_fSpecular[1], a_fSpecular[2], a_fSpecular[3]);

	light.setPosition(a_fPosition[0], a_fPosition[1], a_fPosition[2], a_fPosition[3]);
	light.setSpotDirection(a_fSpotDirection[0], a_fSpotDirection[1], a_fSpotDirection[2]);
	light.setSpotExponent(a_fSpotExponent[0]);
	light.setSpotCutOff(a_fSpotCutOff[0]);
	
	//Add light to vector
	m_vLights.push_back(std::pair<int,Light>(id,light));
}

void Scene::loadCamera(istringstream& iss) {
	int id = 0;
	std::string sAttribute;
	std::string sFilename = "";

	float fPosition[3] = {0.0f,0.0f,0.0f};		//x,y,z
	float fRotation[3] = {0.0f,0.0f,0.0f};		//x,y,z
	
	while (!iss.eof()) {
		removeReturn(iss);
		removeTab(iss);
		getline(iss,sAttribute, '=');
		
		if (sAttribute == "id") {
			readQuotes(iss, id);				//Read attribute value
		}
		else if (sAttribute == "posx") {
			readQuotes(iss,fPosition[0]);
		}
		else if (sAttribute == "posy") {
			readQuotes(iss,fPosition[1]);
		}
		else if (sAttribute == "posz") {
			readQuotes(iss,fPosition[2]);
		}
		else if (sAttribute == "rotx") {
			readQuotes(iss,fRotation[0]);
		}
		else if (sAttribute == "roty") {
			readQuotes(iss,fRotation[1]);
		}
		else if (sAttribute == "rotz") {
			readQuotes(iss,fRotation[2]);
		}
	}
	std::cout << "Loading Camera: " << id << "\t";

	Camera camera;
	camera.setPosition(fPosition[0],fPosition[1],fPosition[2]);
	camera.setRotation(fRotation[0],fRotation[1],fRotation[2]);
	std::pair<int,Camera> data(id,camera);
	m_vCamera.push_back(data);

	std::cout << "Created\t";
}

void Scene::loadModel(istringstream& iss) {
	int id = 0;
	std::string sAttribute;
	std::string sFilename = "";
	Model model;
	int iEnableLight = true;
	int iEnableTexture = true;

	int iModelDataID = 0;
	int iTextureID = 0;
	float fPosition[3] = {0.0f,0.0f,0.0f};		//x,y,z
	float fRotation[3] = {0.0f,0.0f,0.0f};		//x,y,z
	float fScale[3] = {1.0f,1.0f,1.0f};			//x,y,z

	while (!iss.eof()) {
		removeReturn(iss);
		removeTab(iss);
		getline(iss,sAttribute, '=');
		
		if (sAttribute == "id") {
			readQuotes(iss, id);					//Read attribute value
		} 
		else if (sAttribute == "filename") {
			readQuotes(iss, sFilename);	
		}
		else if (sAttribute == "dataID") {
			readQuotes(iss,iModelDataID);			//Read attribute value
		} 
		else if (sAttribute == "textureID") {
			readQuotes(iss,iTextureID);
		} 
		else if (sAttribute == "materialID") {
			int i;
			readQuotes(iss,i);
			model.setMaterial(getMaterial(i));		//Set Material
		}
		//Read Position
		else if (sAttribute == "posx") { readQuotes(iss,fPosition[0]); }
		else if (sAttribute == "posy") { readQuotes(iss,fPosition[1]); }
		else if (sAttribute == "posz") { readQuotes(iss,fPosition[2]); }
		//Read Rotation
		else if (sAttribute == "rotx") { readQuotes(iss,fRotation[0]); }
		else if (sAttribute == "roty") { readQuotes(iss,fRotation[1]); }
		else if (sAttribute == "rotz") { readQuotes(iss,fRotation[2]); }
		//Read Scale
		else if (sAttribute == "scalex") { readQuotes(iss,fScale[0]); }
		else if (sAttribute == "scaley") { readQuotes(iss,fScale[1]); }
		else if (sAttribute == "scalez") { readQuotes(iss,fScale[2]); } 
		else if (sAttribute == "enablelight") { readQuotes(iss,iEnableLight); }
		else if (sAttribute == "enabletexture") { readQuotes(iss,iEnableTexture); }
	}

	std::cout << "Loading Model: " << id << "\t";
	
	ModelData* modelData = &getModelData(iModelDataID);		//Set ModelData and Texture
	modelData->setTexture(getTexture(iTextureID));

	//Set Transformation
	model.setPosition(fPosition[0],fPosition[1],fPosition[2]);
	model.setRotation(fRotation[0],fRotation[1],fRotation[2]);
	model.setScale(fScale[0],fScale[1],fScale[2]);

	model.setModel(getModelData(iModelDataID));
	model.enableLight(iEnableLight != 0);			// Using (!= 0) removes forcing int to bool warning
	model.enableTexture(iEnableTexture != 0);

	//Add model to vector
	std::pair<int,Model> data(id,model);
	m_vModels.push_back(data);							
	std::cout << "Created " << sFilename << "\t";
}

void Scene::readQuotes(istringstream& iss, int& value) {
	iss.get();		//Read open quote
	iss >> value;
	iss.get();		//read end quote
	iss.get();		//read empty space
}

void Scene::readQuotes(istringstream& iss, float& value) {
	iss.get();		//Read open quote
	iss >> value;
	iss.get();		//read end quote
	iss.get();		//read empty space
}

void Scene::readQuotes(istringstream& iss, std::string& value) {
	//iss.get();			//Read open quote
	iss >> value;
	value.replace(0,1,"");	//Remove open quotation
	value.pop_back();		//Remove close quotation
}

void Scene::removeReturn(istringstream& iss) {
	//Look for "\n" and read it away
	char c;
	c = iss.peek();
	if (c == ' ' || c == '\n') {
		iss.get();
		removeReturn(iss);
		removeTab(iss);
	}
}

void Scene::removeTab(istringstream& iss) {
	//Look for "\n" and read it away
	char c;
	c = iss.peek();
	if (c == ' ' || c == '\t') {
		iss.get();					//Read
		removeTab(iss);			//Continue to check for ' ' and '\t'
		removeReturn(iss);
	}
}

GLuint& Scene::getTexture(int id) {
	for (std::vector<std::pair<int,GLuint>>::iterator it = m_viTextures.begin(); it != m_viTextures.end(); ++it) {
		if (it->first == id) {
			return it->second;		//Return texture
		}
	}
	return m_viTextures.at(0).second;	//Return default/starting texture
}

ModelData& Scene::getModelData(int id) {
	for (std::vector<std::pair<int,ModelData>>::iterator it = m_vModelData.begin(); it != m_vModelData.end(); ++it) {
		if (it->first == id) {
			return it->second;		//Return modelData
		}
	}
	return m_vModelData.at(0).second;	//Return default/starting model
}

Material& Scene::getMaterial(int id) {
	for (std::vector<std::pair<int,Material>>::iterator it = m_vMaterial.begin(); it != m_vMaterial.end(); ++it) {
		if (it->first == id) {
			return it->second;		//Return material
		}
	}
	return m_vMaterial.at(0).second;	//Return default material
}

void Scene::update(float h) {
	//Update Active camera
	for (auto it = m_vCamera.begin(); it != m_vCamera.end(); ++it) {
		if (it->first == m_uiCamera) {
			it->second.update(h);
		}
	}

	//Move aircraft
	Vector3D vPos = m_vModels.at(9).second.getPosition();
	float fSpeed = 300.0f;
	m_vModels.back().second.setPosition(vPos.getX(),vPos.getY(),vPos.getZ() + fSpeed * h);
	if (m_vModels.back().second.getPosition().getZ() > 500.0f) {
		m_vModels.back().second.setPosition(vPos.getX(),vPos.getY(),-500.0f);
	}
}

void Scene::draw() {
	//Draw Camera
	for (auto it = m_vCamera.begin(); it != m_vCamera.end(); ++it) {
		//Able to switch to different cameras
		if (it->first == m_uiCamera) {
			it->second.draw();
		}
	}
	//Draw Lights
	for (auto it = m_vLights.begin(); it != m_vLights.end(); ++it) {
		glPushMatrix();
		it->second.draw();
		glPopMatrix();
	}
	//Draw Models
	for (auto it = m_vModels.begin(); it != m_vModels.end(); ++it) {
		it->second.draw();
	}
}

Camera* Scene::getCamera() {
	std::vector<std::pair<int,Camera>>::iterator it;
	for (it = m_vCamera.begin() ; it != m_vCamera.end(); ++it) {
		if (it->first == m_uiCamera) {
			return &it->second;
		}
	}
	//Camera not found
	std::cerr << "Current camera not found\n";
	it = m_vCamera.begin();
	return &it->second;
}