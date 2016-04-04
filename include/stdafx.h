// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include <stdio.h>
#include <tchar.h>

// TODO: reference additional headers your program requires here
#define GL_GLEXT_PROTOTYPES 1		// ALLOW USE OF OPEN GL 1.5+ functionality!!!
#define GLEW_STATIC
// this needs to be the first include
#include <SFML\glew.h>		// make 1.5 functions into function pointers - bind at runtime.
#include <SFML\OpenGL.hpp>	// glew BEFORE opengl headers!!!!
#include <SFML\Graphics.hpp>
// put these inside the SFML\include folder
#include <SFML\wglext.h>
#include <SFML\glext.h>
// note weve also added the lib file glew32s.lib


// shader.h included these
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include <algorithm>

#define _USE_MATH_DEFINES
#include <cmath>