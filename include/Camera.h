/*
	Code used for camera rotation
	https://github.com/dchhetri/OpenGL-City/blob/master/opengl_camera.cpp
*/

#ifndef CAMERA_H
#define CAMERA_H

#include "Transformable.h"
#include <SFML/glew.h>
#include <cmath>
#include <SFML\wglext.h>
#include <SFML\glext.h>
#include <iostream>
#include <SFML/System/Clock.hpp>

#include "KeyPressObserver.h"

class Camera: public Transformable, public KeyPressObserver{
private:
	Vector3D m_vDirection;
	Vector3D m_vRight;
	Vector3D m_vUp;
	Vector3D m_vOldRotation;

	Vector3D m_vLSight;			//!< Line of sight		
	float m_fSpeed;				//!< Camera move speed
	float m_fRotationSpeed;		//!< Speed of camera rotation
	float m_fSpeedH;			//!< Speed multiplied by timestep
	float m_fRotationSpeedH;	//!< Speed multiplied by timestep
private:
	void updateRotationX();
	void updateRotationY();
	void updateRotationZ();

	void computeRight();
	void computeUp();

protected:
		void keysUpdated(KeyPressEvent* state);		//!< Function called when key event occurs
public:
	Camera();				//!< Default Constructor

	void setMoveSpeed(float Speed);
	void setRotationSpeed(float Speed);

	void update(float timeStep);
	void draw();

	void goForward();
	void goBackward();
	void goLeft();
	void goRight();
	void goUp();
	void goDown();

	void turnLeft();
	void turnRight();
	void lookUp();
	void lookDown();

	void tiltLeft();
	void tiltRight();
};

#endif