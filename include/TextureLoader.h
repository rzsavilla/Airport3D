#pragma once

#include "stdafx.h"

using namespace std;



class TextureLoader
{
public:
	TextureLoader(void);
	~TextureLoader(void);

	int LoadBMP(string location, GLuint &texture); 
};

