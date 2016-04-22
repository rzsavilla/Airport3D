#ifndef GAME_H
#define GAME_H

#include "KeyPressEvent.h"
#include "KeyPressSub.h"
#include "TextureLoader.h"
#include "ModelReader.h"
#include "Model.h"
#include "Camera.h"
#include "Scene.h"

#include <SFML/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/wglext.h>
#include <SFML/glext.h>

class Game {
private:
	Scene scene;
private:
	////////////////////WINDOW////////////////////////
	const int m_kiWindowWidth;				//!< Window Width
	const int m_kiWindowHeight;				//!< Window Height
	const float m_kfRefreshRate;			//!< Refresh Rate
	sf::Vector2i m_vWindowSize;				//!< Window Size, Width and Height
	sf::ContextSettings m_Context;			//!< Window Settings
	sf::Window m_Window;					//!< Everything is rendered onto this window
	sf::ContextSettings m_WindowSettings;	//!< Window Settings
private:
	///////////////////INPUTS///////////////////////
	sf::Event m_Event;				//!< Event for user input
	KeyPressEvent m_KeyPress;		//!< Keypress event records key presses
	KeyPressSub m_KeyPressSub;		//!< Notifies subscribers of any changes/updates to KeyPressEvent
private:
	///////////////////Timers///////////////////////
	sf::Clock m_TimeStep;			//!< Timestep for euler intergration
	sf::Clock m_Elapsed;			//!< Elapsed time
private:
	/////////////Game Loop///////////////////////////
	void handleEvents();				//!< Update inputs
	void update(sf::Time timer);		//!< Update program logic
	void render();						//!< Render the program

public:
	Game();			//!< Default constructor
	~Game();		//!< Destructor
	void run();		//!< Run the game loop
};

#endif