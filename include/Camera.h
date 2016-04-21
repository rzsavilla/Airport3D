/*! \class Camera
	\brief OpenGL glu lookat Camera
	Camera object is able to look around in 3D space, panning tilting and moving forwards, backwards upwards and downwards 
	Using worldspace coordinate system	
*/

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
	//World Space Coordinates
	Vector3D m_vDirection;		//!< Camera Orientation
	Vector3D m_vRight;			//!< Right = Direction cross Up 
	Vector3D m_vUp;				//!< Up Vector
	Vector3D m_vOldRotation;	//!< Cameras previous rotation, used to compute angle difference to rotate the camera

	Vector3D m_vLSight;			//!< Line of sight		
	float m_fSpeed;				//!< Camera move speed
	float m_fRotationSpeed;		//!< Speed of camera rotation
	float m_fSpeedH;			//!< Speed multiplied by timestep
	float m_fRotationSpeedH;	//!< Speed multiplied by timestep
private:
	//Update View Orientation
	void updateRotationX();		//!< Rotates directione around the right Vector
	void updateRotationY();		//!< Rotates direction around the up vector
	void updateRotationZ();		//!< Rotates right around the up vector

	void computeRight();		//!< Right = Direction cross Up
	void computeUp();			//!< UP = Direction cross Right

protected:
		void keysUpdated(KeyPressEvent* state);		//!< Function called when key event occurs
public:
	Camera();				//!< Default Constructor

	void setMoveSpeed(float Speed);			//!< Set Camera movement speed \param Speed	New Speed
	void setRotationSpeed(float Speed);		//!< Set Camera rotation speed \param Speed New Speed

	void update(float timeStep);	//!< Update the camera transformations
	void draw();					//!< Position and drwa the camera view

	//Move
	void goForward();		//!< Increases z position
	void goBackward();		//!< Decreases z position
	void goLeft();			//!< Decreases x position
	void goRight();			//!< Increases x position
	void goUp();			//!< Increases y position
	void goDown();			//!< Decreases y position

	//Yaw
	void turnLeft();		//!< Increase yaw
	void turnRight();		//!< Decrease yaw
	//Pitch
	void lookUp();			//!< Increase pitch
	void lookDown();		//!< Decrease pitch
	//Roll
	void tiltLeft();		//!< Roll to the left
	void tiltRight();		//!< Roll to the right
};

#endif