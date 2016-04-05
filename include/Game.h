#ifndef GAME_H
#define GAME_H



#include "KeyPressEvent.h"
#include "KeyPressSub.h"
#include "TextureLoader.h"
#include "ModelReader.h"
#include "Model.h"

#include <SFML/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/wglext.h>
#include <SFML/glext.h>

class Game {
private:
	////////////////////WINDOW////////////////////////
	const int m_kiWindowWidth;
	const int m_kiWindowHeight;
	const float m_kfRefreshRate;
	sf::Vector2i m_vWindowSize;
	sf::ContextSettings m_Context;
	sf::Window m_Window;
	sf::ContextSettings m_WindowSettings;
private:
	///////////////////LOADERS///////////////////////
	TextureLoader* m_TextureLoader;
	ModelReader* m_ModelReader;

	GLuint m_textures[2];
private:
	///////////////////MODELS///////////////////////
	ModelData modelData;
	Model model;
private:
	///////////////////INPUTS///////////////////////
	sf::Event m_Event;
	KeyPressEvent m_KeyPress;
	KeyPressSub m_KeyPressSub;
private:
	//timers
	sf::Clock m_TimeStep;
	sf::Clock m_Elapsed;
private:
	/////////////Game Loop///////////////////////////
	void handleEvents();
	void update(float h);
	void render();

	float m_lightPosition[4];
	void configureLightSources();
	void SetLightPosition(float x, float y, float z);
	void SetMaterialWhite();
public:
	Game();
	~Game();
	void run();				//!< Run the game loop
};

#endif