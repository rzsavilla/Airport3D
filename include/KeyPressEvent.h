#ifndef KEYPRESSEVENT_H
#define KEYPRESSEVENT_H

#include <SFML/Window/Keyboard.hpp>
#include <vector>

class KeyPressEvent {
private:
	/*
	bool bW;			//!< W key
	bool bS;			//!< S key
	bool bA;			//!< A key
	bool bD;			//!< D key
	bool bUp;			//!< Up arrow key
	bool bDown;			//!< Down arrow key
	bool bLeft;			//!< Left arrow key
	bool bRight;		//!< Right arrow key		
	bool bSpace;		//!< Space key
	bool bEscape;		//!< Escape key
	bool bLeftShift;	//!< Left Shift Key
	*/

	std::vector<std::pair<sf::Keyboard::Key,bool>> m_vKeyPressed;
public:
	KeyPressEvent();		//!< Default Contructor
	bool pressed(sf::Keyboard::Key key);
	void update(sf::Keyboard::Key key, bool isPressed);

	void resetKeys();
};

#endif