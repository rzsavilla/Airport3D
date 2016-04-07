#include "Camera.h"
using namespace sf;

Camera::Camera() {
	m_fSpeed = 5000.f;
	m_fRotationSpeed = 800.f;
	m_fSpeedH = 0.0f;
	m_fRotationSpeedH = 0.0f;

	setPosition(0.0f,0.0f,0.0f);
	setRotation(0.0f,0.0f,0.0f);
	
	m_vLSight = Vector3D(0.0f,0.0f,0.0f);

	m_vRight = Vector3D(1.0f,0.0f,0.0f);
	m_vDirection = Vector3D(0.0f,0.0f,-1.0f);
	m_vUp = Vector3D(0.0f,1.0f,0.0f);

	m_vRight = m_vRight.unitVector();
	m_vDirection = m_vDirection.unitVector();
	m_vUp = m_vUp.unitVector();
}

void Camera::keysUpdated(KeyPressEvent* state) {
	//Movement
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
	//std::cout << timeStep.asSeconds() << std::endl;
}

void Camera::draw() {
	m_vLSight = m_vPosition + m_vDirection;

	gluLookAt(
		m_vPosition.getX(),m_vPosition.getY(),m_vPosition.getZ(),
		m_vLSight.getX(),m_vLSight.getY(),m_vLSight.getZ(),
		m_vUp.getX(),m_vUp.getY(),m_vUp.getZ()
		);
}

void Camera::computeDir() {

}
void Camera::computeRight() {
	m_vRight = m_vDirection.crossProduct(m_vUp);
}
void Camera::computeUp() {
	m_vUp = m_vDirection.crossProduct(m_vRight) * -1;
}

void Camera::goForward() {
	m_vPosition += (m_vDirection * m_fSpeedH);
}
void Camera::goBackward() {
	m_vPosition -= (m_vDirection * m_fSpeedH);
}
void Camera::goLeft() {
	m_vPosition -= (m_vRight * m_fSpeedH);
}
void Camera::goRight() {
	m_vPosition += (m_vRight * m_fSpeedH);
}
void Camera::goUp() {
	m_vPosition += (m_vUp * m_fSpeedH);
}
void Camera::goDown() {
	m_vPosition -= (m_vUp * m_fSpeedH);
}

void Camera::lookUp() {
	//Increase angle
	m_vRotation.setX (m_vRotation.getX() + m_fRotationSpeedH);

	m_vDirection = m_vDirection * cos(m_fRotationSpeedH * (3.141 / 180.0f)) +
				   m_vUp * sin(m_fRotationSpeedH * (3.141 / 180.0f));
	
	m_vDirection = m_vDirection.unitVector();	//Normalize

	computeUp();
}

void Camera::lookDown() {
	///Increase angle
	m_vRotation.setX (m_vRotation.getX() - m_fRotationSpeedH);


	m_vDirection = m_vDirection * cos(m_fRotationSpeedH * (3.141 / 180.0f)) -
				   m_vUp * sin(m_fRotationSpeedH * (3.141 / 180.0f));
	
	m_vDirection = m_vDirection.unitVector();	//Normalize

	computeUp();
}

void Camera::turnLeft() {
	//Increase angle
	m_vRotation.setY (m_vRotation.getY() - m_fRotationSpeedH);


	m_vDirection = m_vDirection * cos(m_fRotationSpeedH * (3.141 / 180.0f)) -
				   m_vRight * sin(m_fRotationSpeedH * (3.141 / 180.0f));

	m_vDirection = m_vDirection.unitVector();	//Normalize

	computeRight();
}

void Camera::turnRight() {
	//Increase angle
	m_vRotation.setY (m_vRotation.getY() + m_fRotationSpeedH);

	m_vDirection = m_vDirection * cos(m_fRotationSpeedH * (3.141 / 180.0f)) +
				   m_vRight * sin(m_fRotationSpeedH * (3.141 / 180.0f));

	m_vDirection = m_vDirection.unitVector();	//Normalize

	computeRight();
}

void Camera::tiltLeft() {
	//Increase angle
	m_vRotation.setZ (m_vRotation.getZ() + m_fRotationSpeedH);

	m_vRight = m_vRight * cos(m_fRotationSpeedH * (3.141 / 180.0f)) +
				   m_vUp * sin(m_fRotationSpeedH * (3.141 / 180.0f));

	m_vDirection = m_vDirection.unitVector();	//Normalize

	computeUp();
}
void Camera::tiltRight() {
	//Increase angle
	m_vRotation.setZ (m_vRotation.getZ() + m_fRotationSpeedH);

	m_vRight = m_vRight * cos(m_fRotationSpeedH * (3.141 / 180.0f)) -
				   m_vUp * sin(m_fRotationSpeedH * (3.141 / 180.0f));

	m_vDirection = m_vDirection.unitVector();	//Normalize

	computeUp();
}