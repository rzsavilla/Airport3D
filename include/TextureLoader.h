#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include "stdafx.h"

using namespace std;

class TextureLoader
{
public:
	TextureLoader(void);		//!< Default Constructor
	~TextureLoader(void);		//!< Destructor

	int LoadBMP(string location, GLuint &texture); 
};

#endif
