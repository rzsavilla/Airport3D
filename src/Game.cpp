#include "Game.h"

Game::Game()
	:m_kiWindowWidth(1280)
	,m_kiWindowHeight(1024)
	,m_kfRefreshRate(0.0f)
{
	int depthBits = 24;
	int stencilBits = 8;
	int antiAliasingLevel = 2;
	int majorVersion = 3;
	int minorVersion = 3;

	m_Context = sf::ContextSettings(depthBits,stencilBits,antiAliasingLevel,majorVersion,minorVersion);
	m_Window.create(sf::VideoMode(m_kiWindowWidth,m_kiWindowHeight,32), "Airport", 7U, m_Context);
	m_WindowSettings = m_Window.getSettings();
	m_Window.setFramerateLimit(60.0f);

	//Color and depth clear value
	glClearDepth(1.f);
	glClearColor(0.0196f,0.6,250.f,0.8f);

	// Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

	// draw single sided faces
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

    // Setup a perspective projection
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0f, (float)m_kiWindowWidth/m_kiWindowHeight, 0.1f, 5000.f);

	scene.loadScene("scene1.xml");					//Load the Scene
	m_KeyPressSub.attach(scene.getCamera());	
}

Game::~Game() {

}

void Game::run() {
	while(m_Window.isOpen()) {
		//Game Loop
		handleEvents();
		if (m_Elapsed.getElapsedTime().asSeconds() > m_kfRefreshRate) {
			update(m_TimeStep.restart());
			render();
		}
	}
}

void Game::handleEvents() {
	while (m_Window.pollEvent(m_Event)) {
		if (m_Event.type == sf::Event::Closed) {
			m_Window.close();						//Close Window
		}

		//Keyboard Inputs
		if (m_Event.type == sf::Event::KeyPressed) {
			m_KeyPress.update(m_Event.key.code, true);		//Update Keys pressed
			m_KeyPressSub.notify(&m_KeyPress);					//Notify all subscribers
			

			if (m_Event.key.code == sf::Keyboard::Escape)
				m_Window.close();
		}
		if (m_Event.type == sf::Event::KeyReleased) {
			m_KeyPress.update(m_Event.key.code, false);	    //Update Keys released
			m_KeyPressSub.notify(&m_KeyPress);					//Notify all subscribers
		}
		//Mouse Inputs
	}
}

void Game::update(sf::Time timer) {
	scene.update(0.001);
}

void Game::render() {
	m_Window.setActive();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	scene.draw();

	m_Elapsed.restart();
	m_Window.display();
}