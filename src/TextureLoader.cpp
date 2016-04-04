#include "stdafx.h"
#include "TextureLoader.h"


TextureLoader::TextureLoader(void)
{
}


TextureLoader::~TextureLoader(void)
{
}


// Original code from
//
// http://www.cplusplus.com/articles/GwvU7k9E/
//
//
// this loads and binds the texture to a given open gl identifier
int TextureLoader::LoadBMP(string location, GLuint &texture)  //const char* location
{
	// this is a version using c++ file i/o rather than c.
	unsigned char* datBuff[2] = {nullptr, nullptr}; // Header buffers

	unsigned char* pixels = nullptr; // Pixels

	// windows knows the relevant header structures
	BITMAPFILEHEADER* bmpHeader = nullptr; // Header
	BITMAPINFOHEADER* bmpInfo   = nullptr; // Info

	// The file... We open it with it's constructor
	std::ifstream file(location, std::ios::binary);
	if(!file)
	{
		std::cout << "Failure to open bitmap file.\n";
		return 1;
	}	
	// Allocate byte memory that will hold the two headers
	datBuff[0] = new unsigned char[sizeof(BITMAPFILEHEADER)];
	datBuff[1] = new unsigned char[sizeof(BITMAPINFOHEADER)];

	file.read((char*)datBuff[0], sizeof(BITMAPFILEHEADER));
	file.read((char*)datBuff[1], sizeof(BITMAPINFOHEADER));

	// Construct the values from the buffers
	bmpHeader = (BITMAPFILEHEADER*) datBuff[0];
	bmpInfo   = (BITMAPINFOHEADER*) datBuff[1];

	// Check if the file is an actual BMP file 0x42 = 'B'  4D = 'M'
	if(bmpHeader->bfType != 0x4D42)
	{
		std::cout << "File \"" << location << "\" Not a bitmap file (wrong header)\n";
		return 2;
	}

	if (bmpInfo->biBitCount != 24)
	{
		std::cout << "File \"" << location << "\" bits per pixel must be 24\n";
		return 2;
	}

	if (bmpInfo->biPlanes != 1)
	{
		std::cout << "File \"" << location << "\" more than one plane\n";
		return 2;
	}

	unsigned int imageSize = bmpInfo->biSizeImage;
	unsigned int numberOfPixels = imageSize / 3;

	if (imageSize == 0) {
		numberOfPixels = bmpInfo->biWidth * bmpInfo->biHeight;
		imageSize = numberOfPixels * 3;
	}
	
	// First allocate pixel memory
	pixels = new unsigned char[imageSize];

	// Go to where image data starts, then read in image data
	file.seekg(bmpHeader->bfOffBits);
	file.read((char*)pixels, imageSize);
	
	// We're almost done. We have our image loaded, however it's not in the right format.
	// .bmp files store image data in the BGR format, and we have to convert it to RGB.
	// Since we have the value in bytes, this shouldn't be to hard to accomplish

	unsigned char tmpRGB = 0; // Swap buffer
	for (unsigned long i = 0; i < (3 * numberOfPixels); i += 3)
	{
		tmpRGB        = pixels[i];
		pixels[i]     = pixels[i + 2];
		pixels[i + 2] = tmpRGB;
	}

	// Set width and height to the values loaded from the file
	GLuint w = bmpInfo->biWidth;
	GLuint h = bmpInfo->biHeight;
	
/*******************GENERATING TEXTURES*******************/

	glGenTextures(1, &texture);             // Generate a texture
	glBindTexture(GL_TEXTURE_2D, texture); // Bind that texture temporarily

	GLint mode = GL_RGB;                   // Set the mode

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	 
	// Create the texture. We get the offsets from the image, then we use it with the image's
	// pixel data to create it.
	glTexImage2D(GL_TEXTURE_2D, 0, mode, w, h, 0, mode, GL_UNSIGNED_BYTE, pixels);

	// do we clamp the textures??
#if 0
	// -----------------------------------------------------------
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//------------------------------------------------------------
#endif
	// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, NULL);

	// Output a successful message
	std::cout << "Texture \"" << location << "\" successfully loaded.\n";

	// Delete the buffers.
	delete[] datBuff[0];
	delete[] datBuff[1];
	delete[] pixels;

	return 0; // Return success code 	
}