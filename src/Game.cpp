#include "Game.h"

Game::Game()
	:m_kiWindowWidth(1280)
	,m_kiWindowHeight(1024)
	,m_kiRefreshRate(0.03f)
{
	int depthBits = 24;
	int stencilBits = 8;
	int antiAliasingLevel = 2;
	int majorVersion = 3;
	int minorVersion = 3;

	m_Context = sf::ContextSettings(depthBits,stencilBits,antiAliasingLevel,majorVersion,minorVersion);
	m_Window.create(sf::VideoMode(m_kiWindowWidth,m_kiWindowHeight,m_kiRefreshRate), "Airport", 7U, m_Context);
	m_WindowSettings = m_Window.getSettings();

	//Color and depth clear value
	glClearDepth(1.f);
	glClearColor(0.f,0.f,0.f,0.f);

	// Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

	// draw single sided faces
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

    // Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, (float)m_kiWindowWidth/m_kiWindowHeight, 1.f, 500.f);


	configureLightSources();

	m_TextureLoader = new TextureLoader();

	//m_ModelReader = new ModelReader();
}

Game::~Game() {
	delete m_TextureLoader;
}

void Game::run() {

	while(m_Window.isOpen()) {
		handleEvents();
		update(m_TimeStep.getElapsedTime().asSeconds());
		render();
		m_TimeStep.restart();
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

void Game::update(float h) {

}

void Game::render() {
	m_Window.setActive();

	if (m_Elapsed.getElapsedTime().asSeconds() > m_kiRefreshRate) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		glPopMatrix();


		m_Elapsed.restart();
		m_Window.display();
	}
	
}

void Game::configureLightSources() {
	GLfloat lightColour[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat noLight[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat lightModelAmbient[] = {0.3f, 0.3f, 0.3f, 1.0};

	// put light behind and above us on left
	SetLightPosition(0.0f, m_lightPosition[1], m_lightPosition[2]);

	glLightfv(GL_LIGHT0, GL_POSITION, m_lightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColour);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightColour);
	glLightfv(GL_LIGHT0, GL_AMBIENT, noLight);			// no ambient light from the source

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightModelAmbient);	// use global ambient instead

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// with lighting glColor no longer applies
	// create a default material for the models
	SetMaterialWhite();
}

void Game::SetLightPosition(float x, float y, float z)
{
	m_lightPosition[0] = x;
	m_lightPosition[1] = y;
	m_lightPosition[2] = z;
}

void Game::SetMaterialWhite()
{
	GLfloat materialWhiteAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat materialWhiteDiffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
	GLfloat materialWhiteSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};		// so keeps light colour
	GLfloat materialWhiteShininess = 4.0f;
	glShadeModel(GL_SMOOTH);
	//glShadeModel(GL_FLAT);
	glMaterialfv(GL_FRONT,GL_AMBIENT, materialWhiteAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialWhiteDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialWhiteSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, materialWhiteShininess);
}