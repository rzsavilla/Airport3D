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
	char c;
	std::string sLine;
	std::string sToken = "";
	while (getline(sceneFile, sLine, '\>')) {		//Read everything withing the '\>'
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
	std::string sFilename;

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

void Scene::loadModelData(istringstream& iss) {
	int id = 0;
	std::string sAttribute;
	std::string sFilename;
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
	}

	std::cout << "Loading: " << sFilename << "\t";

	if (!sFilename.empty()) {
		//Store the ModeData
		ModelReader reader;
		std::pair<int,ModelData> data(id,reader.ReadModelObjData(m_sModelBaseDir+sFilename));
		m_vModelData.push_back(data);
		std::cout << "Loaded\t";
		return;
	}
	std::cout << "Failed\t";
}

void Scene::loadLight(istringstream& iss) {
	std::string sAttribute;
	int id = 0;
	//Default values
	GLfloat fLight[4] = { 1.0f, 1.0f, 1.0f, 1.0f};			//White light			
	GLfloat fNoLight[4] = { 0.0f, 0.0f, 0.0f, 0.0f};				
	GLfloat fAmbient[4] = { 0.1f, 0.1f, 0.1f, 1.0f};	
	GLfloat fPosition[4] = { 0.0f, 1000.0f, 0.0f, 0.0f};			
	GLfloat fRotation[3]  = { 0.0f, 0.0f, 0.0f};				
	
	Light light;

	while (!iss.eof()) {
		removeReturn(iss);
		removeTab(iss);
		getline(iss,sAttribute, '=');
		if (sAttribute == "id") {
			readQuotes(iss, id);				//Read attribute value
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
		// Read Position
		else if (sAttribute == "posx") { readQuotes(iss,fPosition[0]); }
		else if (sAttribute == "posy") { readQuotes(iss,fPosition[1]); }
		else if (sAttribute == "posz") { readQuotes(iss,fPosition[2]); }
		// Read Rotation
		else if (sAttribute == "rotx") { readQuotes(iss,fRotation[0]); }
		else if (sAttribute == "roty") { readQuotes(iss,fRotation[1]); }
		else if (sAttribute == "rotz") { readQuotes(iss,fRotation[2]); }
		// Read Light Colour
		else if (sAttribute == "lightR") { readQuotes(iss,fLight[0]); }
		else if (sAttribute == "lightG") { readQuotes(iss,fLight[1]); }
		else if (sAttribute == "lightB") { readQuotes(iss,fLight[2]); }
		else if (sAttribute == "lightA") { readQuotes(iss,fLight[3]); }
		// Read No Light colour
		else if (sAttribute == "nolightR") { readQuotes(iss,fNoLight[0]); }
		else if (sAttribute == "nolightG") { readQuotes(iss,fNoLight[1]); }
		else if (sAttribute == "nolightB") { readQuotes(iss,fNoLight[2]); }
		else if (sAttribute == "nolightA") { readQuotes(iss,fNoLight[3]); }
		// Read Ambient light
		else if (sAttribute == "ambientR") { readQuotes(iss,fAmbient[0]); }
		else if (sAttribute == "ambientG") { readQuotes(iss,fAmbient[1]); }
		else if (sAttribute == "ambientB") { readQuotes(iss,fAmbient[2]); }
		else if (sAttribute == "ambientA") { readQuotes(iss,fAmbient[3]); }

	}
	//Set transformation
	light.setPosition(fPosition[0], fPosition[1], fPosition[2]);
	light.setRotation(fRotation[0], fRotation[1], fRotation[2]);

	//Set light properties
	light.setLightColour(fLight[0], fLight[1], fLight[2] , fLight[3]);
	light.setNoLightColour(fNoLight[0], fNoLight[1], fNoLight[2] , fNoLight[3]);
	light.setLightModelAmbient(fAmbient[0], fAmbient[1], fAmbient[2], fAmbient[3]);
	
	//Add light to vector
	m_vLights.push_back(std::pair<int,Light>(id,light));	
}

void Scene::loadCamera(istringstream& iss) {
	int id = 0;
	std::string sAttribute;

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
		else if (sAttribute == "dataID") {
			readQuotes(iss,iModelDataID);			//Read attribute value
		} 
		else if (sAttribute == "textureID") {
			readQuotes(iss,iTextureID);
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
		else if (sAttribute == "scalex") {
			readQuotes(iss,fScale[0]);
		}
		else if (sAttribute == "scaley") {
			readQuotes(iss,fScale[1]);
		}
		else if (sAttribute == "scalez") {
			readQuotes(iss,fScale[2]);
		}
	}

	std::cout << "Loading Model: " << id << "\t";
	Model model;
	ModelData* modelData = &getModelData(iModelDataID);		//Set ModelData and Texture
	modelData->setTexture(getTexture(iTextureID));

	model.setPosition(fPosition[0],fPosition[1],fPosition[2]);
	model.setRotation(fRotation[0],fRotation[1],fRotation[2]);
	model.setScale(fScale[0],fScale[1],fScale[2]);
	model.setModel(getModelData(iModelDataID));
	std::pair<int,Model> data(id,model);
	m_vModels.push_back(data);							//Add model to vector
	std::cout << "Created\t";
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

void Scene::update(float h) {
	
	//Update Active camera
	for (auto it = m_vCamera.begin(); it != m_vCamera.end(); ++it) {
		if (it->first == m_uiCamera) {
			it->second.update(h);
		}
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
		it->second.draw();
	}

	//Draw Models
	for (auto it = m_vModels.begin(); it != m_vModels.end(); ++it) {
		it->second.draw();
	}
}

Camera* Scene::getCamera() {
	for (auto it = m_vCamera.begin(); it != m_vCamera.end(); ++it) {
		if (it->first == m_uiCamera) {
			return &it->second;
		}
	}
}