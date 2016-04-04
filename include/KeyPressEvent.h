#ifndef KEYPRESSEVENT_H
#define KEYPRESSEVENT_H

#include <SFML/Window/Keyboard.hpp>

class KeyPressEvent {
public:
	bool bW;	 //!< W key
	bool bS;	 //!< S key
	bool bA;	 //!< A key
	bool bD;	 //!< D key
	bool bUp;	 //!< Up arrow key
	bool bDown;	 //!< Down arrow key
	bool bLeft;	 //!< Left arrow key
	bool bRight; //!< Right arrow key		
	bool bSpace; //!< Space key
	bool bEscape;//!< Escape key
public:
	KeyPressEvent();		//!< Default Contructor
	void update(sf::Keyboard::Key key, bool isPressed);
};

#endif