#include "stdafx.h"
#include "ModelReader.h"

ModelReader::ModelReader() {
	bHasNormals = false;
}

ModelReader::ModelReader(string filename)
{
	bHasNormals = false;
	ReadModelObjData(filename);
}

ModelReader::~ModelReader(void)
{

}

ModelData ModelReader::ReadModelObjData(string filename)
{
	std::fstream modelfile(filename, std::ios_base::in);

	if(!modelfile.is_open())
	{
		std::cerr << "File " << filename << " not found.";
		DebugBreak();
		throw std::invalid_argument( "File not found" );
		//return;	//ERROR!!!
	}

	string line;
	string token = "";
	while (getline(modelfile, line))
	{
		istringstream iss(line);

		// process the line
		token = "";

		iss >> token; // read to first whitespace
	
		if (token == "#")
		{
			// ignore rest of line
			// iss >> s;
		}
		else if (token == "g")
		{
			// read the model name
			iss >> m_modelName;
			//std::cout << "Loading: " << m_modelName << std::endl;
		}
		else if (token == "v")
		{
			ProcessVertexLine(iss);
		}
		else if (token == "vn")
		{
			ProcessVertexNormalLine(iss);
			if (!bHasNormals) {
				bHasNormals = true;
			}
		}
		else if (token == "vt")
		{
			ProcessVertexTextureLine(iss);
		}
		else if (token == "f")
		{
			ProcessFaceLine(iss);
		}
		else
		{
			// ignore any line without these qualifiers
			// ignore rest of line
		}
	}
	modelfile.close();

	//expand the data suitable for lDrawArrays()
	CreateExpandedVertices();
	CreateExpandedNormals();
	CreateExpandedTextureCoordinates();

	return ModelData(m_vertexTriplets,m_vertexNormalTriplets,m_vertexTexturePairs,bHasNormals);
}

void ModelReader::ProcessVertexLine(istringstream& iss)
{
	// TODO - store 3 floats in m_vertices vector
	float f;
	//std::cout <<  "v ";
	for (int i = 0; i < 3; i++) {
		iss >> f; 
		m_vertices.push_back(f);
		//std::cout << f << " ";
	}
	//std::cout << std::endl;
}

void ModelReader::ProcessVertexNormalLine(istringstream& iss)
{
	// TODO - store 3 floats in m_vertexNormals vector
	float f;
	//std::cout << "vn ";
	for (int i = 0; i < 3; i++) {
		iss >> f; 
		m_vertexNormals.push_back(f);
		//std::cout << f << " ";
	}
	//std::cout << std::endl;
}

void ModelReader::ProcessVertexTextureLine(istringstream& iss)
{
	// TODO - store 2 floats in m_vertexTextureCoordinates vector
	float f;
	//std::cout << "vt "; 
	for (int i = 0; i < 2; i++) {
		iss >> f; 
		m_vertexTextureCoordinates.push_back(f);
		//std::cout << f << " ";
	}
	//std::cout << std::endl;
}

void ModelReader::ProcessFaceLine(istringstream& iss)
{
	// TODO - process 3 types of f line data

	//std::cout << "f ";

	char iChar;
	int j;
	for (int i = 0 ; i < 3; i++) {
		iss >> j;						//Get first number face index
		int lookAhead = iss.peek();
		if (lookAhead == forwardSlash) {				//Look for forward slash
			iss.get();					//read slash
			lookAhead = iss.peek();
			if (lookAhead == forwardSlash) {			//Look for second forward slash
				//Found format: "face//normal" index
				iss.get();										//read slash
				
				//std::cout << j << "//";
				m_faceVertexIndices.push_back(j - 1);		//Store face index

				iss >> j;										//get normal value
				//std::cout << j << " ";
				m_faceNormalIndices.push_back(j - 1);		//Store normal index
			} else {
				//Found format: "face/texture/normal" index

				//std::cout << j;
				//std::cout << "/";
				m_faceVertexIndices.push_back(j - 1);		//Store face index

				iss >> j;										//Read texture index;
				//std::cout << j;
				//std::cout << "/";
				m_faceTextureIndices.push_back(j - 1);		//Store texture index

				iss.get();										//Read slash
				iss >> j;										//Read normal index;
				//std::cout << j << " ";
				m_faceNormalIndices.push_back(j - 1);		//Store normal index
			}
		} else {
			//No slashes only face indices
			//std::cout << j << " ";
			m_faceVertexIndices.push_back(j - 1);	//Store face index
		}
	}
	//std::cout << std::endl;
}


void ModelReader::CreateExpandedVertices()
{
	for (std::vector<unsigned int>::iterator it = m_faceVertexIndices.begin() ; it != m_faceVertexIndices.end(); ++it) {
		int index = *it * 3;
		m_vertexTriplets.push_back(m_vertices.at(index));
		m_vertexTriplets.push_back(m_vertices.at(index + 1));
		m_vertexTriplets.push_back(m_vertices.at(index + 2));
	}
}

void ModelReader::CreateExpandedNormals()
{
	for (std::vector<unsigned int>::iterator it = m_faceNormalIndices.begin(); it != m_faceNormalIndices.end(); ++it) {
		int index = *it * 3;
		m_vertexNormalTriplets.push_back(m_vertexNormals.at(index));
		m_vertexNormalTriplets.push_back(m_vertexNormals.at(index + 1));
		m_vertexNormalTriplets.push_back(m_vertexNormals.at(index + 2));
	}
}
void ModelReader::CreateExpandedTextureCoordinates()
{
	for (std::vector<unsigned int>::iterator it = m_faceTextureIndices.begin(); it != m_faceTextureIndices.end(); ++it) {
		int index = *it * 2;
		m_vertexTexturePairs.push_back(m_vertexTextureCoordinates.at(index));
		m_vertexTexturePairs.push_back(m_vertexTextureCoordinates.at(index + 1));
	}
}

// Get methods gove access to the vector data

vector<float>& ModelReader::GetVertices()
{
	return m_vertexTriplets;
}
vector<float>& ModelReader::GetNormals()
{
	return m_vertexNormalTriplets;
}
vector<float>& ModelReader::GetTextureCoordinates()
{
	return m_vertexTexturePairs;
}