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
    gluPerspective(90.f, (float)m_kiWindowWidth/m_kiWindowHeight, 0.1f, 50000.f);

	SetLightPosition(0.0f,+500.f,0.0f);
	configureLightSources();

	/*
	m_ModelReader = new ModelReader();
	modelData[0] = m_ModelReader->ReadModelObjData("models/map.obj");
	modelData[1] = m_ModelReader->ReadModelObjData("models/hangar.obj");
	modelData[2] = m_ModelReader->ReadModelObjData("models/cessna.obj");

	model[0].setModel(modelData[0]);
	model[1].setModel(modelData[1]);
	model[2].setModel(modelData[2]);

	model[0].setPosition(0.0f,0.0f,0.0f);
	model[1].setPosition(0.0f,0.0f,0.0f);
	model[2].setPosition(0.0f,0.0f,0.0f);


	m_TextureLoader = new TextureLoader();
	m_TextureLoader->LoadBMP("images/lava100.bmp", m_textures[0]);
	m_TextureLoader->LoadBMP("images/hangar.bmp", m_textures[1]);
	modelData[0].setTexture(m_textures[0]);
	modelData[1].setTexture(m_textures[0]);
	*/
	
	camera.setPosition(0.0f,0.0f,10.f);
	
	//model.setOrigin(0.5,0.5,0.5);
	//model.setScale(0.2);

	scene.loadScene("scene1.xml");
	m_KeyPressSub.attach(scene.getCamera());
}

Game::~Game() {
	//delete m_TextureLoader;
	//delete m_ModelReader;
}

void Game::run() {
	m_TimeStep.restart();
	while(m_Window.isOpen()) {
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
float fX = 0.0f;
void Game::update(sf::Time timer) {
	camera.update(0.01f);
	float fSpeed = 50.f;
	//model.setPosition(0.0f,0.0f,fX -= 0.001);
	//model.rotateX(fSpeed * h);
	//model[1].rotateY(fSpeed * timer.asSeconds());
	//model.setScale(0.5f);
	scene.update(0.001);
}

void Game::render() {
	m_Window.setActive();

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
		
	//camera.draw();

	SetMaterialWhite();
	//model[0].draw();
	//model[1].draw();
	scene.draw();

	m_Elapsed.restart();
	m_Window.display();
}

void Game::configureLightSources() {
	GLfloat lightColour[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat noLight[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat lightModelAmbient[] = {0.3f, 0.3f, 0.3f, 1.0};

	// put light behind and above us on left
	SetLightPosition(m_lightPosition[0], m_lightPosition[1], m_lightPosition[2]);
	//SetLightPosition(0.0f,50.f,0.0f);
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