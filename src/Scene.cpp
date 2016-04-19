#include "Scene.h"

Scene::Scene() {
	m_sSceneBaseDir = "scene/";
	m_sModelBaseDir = "models/";
	m_sTextureBaseDir = "images/";
	m_uiCamera = 0;
}

Scene::Scene(std::string filename) {
	m_sSceneBaseDir = "scene/";
	m_sModelBaseDir = "models/";
	m_sTextureBaseDir = "images/";
	m_uiCamera = 0;

	loadScene(filename);
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
		if (sToken == cComment) {
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
		if (it->first == m_uiCamera) {
			it->second.draw();
			light.setRotation(it->second.getRotation().getX(),it->second.getRotation().getY(),it->second.getRotation().getZ());
		}
	}
	glPushMatrix();
	light.draw();
	glPopMatrix();

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