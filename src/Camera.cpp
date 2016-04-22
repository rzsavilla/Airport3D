#include "Camera.h"
using namespace sf;

Camera::Camera() {
	m_fSpeed = 1000.f;
	m_fRotationSpeed = 1000.f;
	m_fSpeedH = 0.0f;
	m_fRotationSpeedH = 0.0f;

	setPosition(1.0f,1.0f,1.0f);
	setRotation(1.0f,1.0f,1.0f);
	
	m_vLSight = Vector3D(0.0f,0.0f,0.0f);

	m_vRight = Vector3D(1.0f,0.0f,0.0f);
	m_vDirection = Vector3D(0.0f,0.0f,-1.0f);
	m_vUp = Vector3D(0.0f,1.0f,0.0f);

	m_vRight = m_vRight.unitVector();
	m_vDirection = m_vDirection.unitVector();
	m_vUp = m_vUp.unitVector();

	m_vOldRotation = Vector3D(0.0f,0.0f,0.0f);
}

void Camera::keysUpdated(KeyPressEvent* state) {
	//Movement
	if (state->pressed(Keyboard::Space)) {
		setRotation(0.0f,0.0f,0.0f);
		setPosition(0.0f,5.0f,0.0f);
	}

	if (state->pressed(Keyboard::LShift)) {
		if (state->pressed(Keyboard::W))										//Go Up Y
			goUp();
		else if (state->pressed(Keyboard::S))									//Go Down Y
			goDown();
	} 
	else {
		if (state->pressed(Keyboard::W))											//Move Forward Z
			goForward();
		else if (state->pressed(Keyboard::S))										//Move backwards Z
			goBackward();
	}

	if (state->pressed(Keyboard::A))											//Move Left X
		goLeft();
	else if (state->pressed(Keyboard::D))										//Move Right; X
		goRight();

	//Yaw 
	if (state->pressed(Keyboard::Left)) {			//Turn left
		turnLeft();
	}
	else if (state->pressed(Keyboard::Right)) {		//Turn right
		turnRight();
	}

	//Pitch
	if (state->pressed(Keyboard::Up)) {				//Look up
		lookUp();
	} 
	else if (state->pressed(Keyboard::Down)) {		//Look down
		lookDown();
	}

	//Roll 
	if (state->pressed(Keyboard::Q)) {				//Roll left
		tiltLeft();
	} 
	else if (state->pressed(Keyboard::E)) {			//Roll right
		tiltRight();
	}

	//std::cout << "Pos: x:" << (int)m_vPosition.getX() << " y:" << (int)m_vPosition.getY() << " z:" << (int)m_vPosition.getX() << std::endl;
	//std::cout << "Los: x:" << (int)m_vLSight.getX() << " y:" << (int)m_vLSight.getY() << " z:" << (int)m_vLSight.getX() << std::endl;
	//std::cout << "vUp: x:" << (int)m_vUp.getX() << " y:" << (int)m_vUp.getY() << " z:" << (int)m_vUp.getX() << std::endl;
}

void Camera::update(float timeStep) {
	m_fSpeedH = m_fSpeed * timeStep;
	m_fRotationSpeedH = m_fRotationSpeed * timeStep;
}

void Camera::draw() {
	if (m_bUpdated) {
		//Rotations changed
		updateRotationX();		//Update
		updateRotationY();
		updateRotationZ();
		m_bUpdated = false;
	}
	
	m_vLSight = m_vPosition + m_vDirection;
	gluLookAt(
		m_vPosition.getX(),m_vPosition.getY(),m_vPosition.getZ(),
		m_vLSight.getX(),m_vLSight.getY(),m_vLSight.getZ(),
		m_vUp.getX(),m_vUp.getY(),m_vUp.getZ()
	);
	//std::cout << m_vRotation.getX() << " " << m_vRotation.getY() << " " << m_vRotation.getZ() << std::endl;
	//std::cout << "Pos " << m_vPosition.getX() << " " << m_vPosition.getY() << " " << m_vPosition.getZ() << std::endl;
}

void Camera::goForward() { move(m_vDirection * m_fSpeedH); }
void Camera::goBackward() { move((m_vDirection * m_fSpeedH) * -1); }
void Camera::goLeft() { move((m_vRight * m_fSpeedH) * -1); }
void Camera::goRight() { move(m_vRight * m_fSpeedH); }
void Camera::goUp() { move(m_vUp * m_fSpeedH); }
void Camera::goDown() { move((m_vUp * m_fSpeedH) * -1); }

void Camera::lookUp() { rotateY(m_fRotationSpeedH); }
void Camera::lookDown() { rotateY(-m_fRotationSpeedH); }
void Camera::turnLeft() { rotateX(-m_fRotationSpeedH); }
void Camera::turnRight() { rotateX(m_fRotationSpeedH); }
void Camera::tiltLeft() { rotateZ(m_fRotationSpeedH); }
void Camera::tiltRight() { rotateZ(-m_fRotationSpeedH); }

/*
	Code used for camera rotation
	https://github.com/dchhetri/OpenGL-City/blob/master/opengl_camera.cpp
*/
void Camera::updateRotationX() {
	//Keep rotation angle between 0-359
	if (m_vRotation.getX() >= 360) {
		m_vRotation.setX(m_vRotation.getX() - 360);
	} else if (m_vRotation.getX() < 0) {
		m_vRotation.setX(m_vRotation.getX() + 360);
	}

	float fAngle = (m_vRotation.getX() - m_vOldRotation.getX()) ;	//Calculate difference
	m_vOldRotation.setX(m_vRotation.getX());						//Update OldRotation


	m_vDirection = m_vDirection * cos(fAngle * (3.141 / 180.0f)) +
					m_vRight * sin(fAngle * (3.141 / 180.0f));

	m_vDirection = m_vDirection.unitVector();						//Normalize

	computeRight();
}
void Camera::updateRotationY() {
	if (m_vRotation.getY() >= 360) {
		m_vRotation.setY(m_vRotation.getY() - 360);
	} else if (m_vRotation.getY() < 0) {
		m_vRotation.setY(m_vRotation.getY() + 360);
	}

	float fAngle = (m_vRotation.getY() - m_vOldRotation.getY());	//Calculate difference		
	
	m_vOldRotation.setY(m_vRotation.getY());						//Update OldRotation	
																				
	m_vDirection = m_vDirection * cos(fAngle * (3.141 / 180.0f)) +
				   m_vUp * sin(fAngle * (3.141 / 180.0f));
	
	m_vDirection = m_vDirection.unitVector();						//Normalize

	computeUp();

	
}
void Camera::updateRotationZ() {
	if (m_vRotation.getZ() >= 360) {
		m_vRotation.setZ(m_vRotation.getZ() - 360);
	} else if (m_vRotation.getZ() < 0) {
		m_vRotation.setZ(m_vRotation.getZ() + 360);
	}

	float fAngle = (m_vRotation.getZ() - m_vOldRotation.getZ());	//Calculate difference
	m_vOldRotation.setZ(m_vRotation.getZ());						//Update OldRotation

	m_vRight = m_vRight * cos(fAngle * (3.141 / 180.0f)) +
				   m_vUp * sin(fAngle * (3.141 / 180.0f));

	//m_vDirection = m_vDirection.unitVector();						//Normalize

	computeUp();
}

void Camera::computeRight() { m_vRight = m_vDirection.crossProduct(m_vUp); }
void Camera::computeUp() { m_vUp = m_vDirection.crossProduct(m_vRight) * -1; }