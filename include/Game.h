#ifndef GAME_H
#define GAME_H



#include "KeyPressEvent.h"
#include "KeyPressSub.h"
#include "TextureLoader.h"
#include "ModelReader.h"

#include <SFML/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/wglext.h>
#include <SFML/glext.h>

class Game {
private:
	const int m_kiWindowWidth;
	const int m_kiWindowHeight;
	const int m_kiRefreshRate;
	sf::Vector2i m_vWindowSize;
	sf::ContextSettings m_Context;
	sf::Window m_Window;
	sf::ContextSettings m_WindowSettings;
private:
	TextureLoader* m_TextureLoader;
	ModelReader* m_ModelReader;
private:
	sf::Event m_Event;
	KeyPressEvent m_KeyPress;
	KeyPressSub m_KeyPressSub;
private:
	sf::Clock m_TimeStep;
	sf::Clock m_Elapsed;
private:
	void handleEvents();
	void update(float h);
	void render();

	float m_lightPosition[3];
	void configureLightSources();
	void SetLightPosition(float x, float y, float z);
	void SetMaterialWhite();
public:
	Game();
	~Game();
	void run();
};

#endif