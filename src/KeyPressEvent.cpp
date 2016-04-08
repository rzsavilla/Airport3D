#include "KeyPressEvent.h"
#include <iostream>
KeyPressEvent::KeyPressEvent() {
	/*
	bW = false;
	bS = false;
	bA = false;
	bD = false;
	bUp = false;
	bDown = false;
	bLeft = false;
	bRight = false;
	bSpace = false;
	bEscape = false;
	bLeftShift = false;
	*/

	/*
		Add keys that will be used to the vector
	*/

	//Movement
	m_vKeyPressed.push_back(std::pair<sf::Keyboard::Key, bool>(sf::Keyboard::W,false));
	m_vKeyPressed.push_back(std::pair<sf::Keyboard::Key, bool>(sf::Keyboard::A,false));
	m_vKeyPressed.push_back(std::pair<sf::Keyboard::Key, bool>(sf::Keyboard::S,false));
	m_vKeyPressed.push_back(std::pair<sf::Keyboard::Key, bool>(sf::Keyboard::D,false));

	//Camera Rotation
	m_vKeyPressed.push_back(std::pair<sf::Keyboard::Key, bool>(sf::Keyboard::Up,false));
	m_vKeyPressed.push_back(std::pair<sf::Keyboard::Key, bool>(sf::Keyboard::Down,false));
	m_vKeyPressed.push_back(std::pair<sf::Keyboard::Key, bool>(sf::Keyboard::Left,false));
	m_vKeyPressed.push_back(std::pair<sf::Keyboard::Key, bool>(sf::Keyboard::Right,false));

	//Camera Roll
	m_vKeyPressed.push_back(std::pair<sf::Keyboard::Key, bool>(sf::Keyboard::Q,false));
	m_vKeyPressed.push_back(std::pair<sf::Keyboard::Key, bool>(sf::Keyboard::E,false));

	m_vKeyPressed.push_back(std::pair<sf::Keyboard::Key, bool>(sf::Keyboard::Escape,false));
	m_vKeyPressed.push_back(std::pair<sf::Keyboard::Key, bool>(sf::Keyboard::Space,false));
	m_vKeyPressed.push_back(std::pair<sf::Keyboard::Key, bool>(sf::Keyboard::BackSpace,false));
	m_vKeyPressed.push_back(std::pair<sf::Keyboard::Key, bool>(sf::Keyboard::LShift,false));
}

void KeyPressEvent::resetKeys() {
	for (auto it = m_vKeyPressed.begin(); it != m_vKeyPressed.end(); ++it) {
		it->second = false;			//Set all keys as released
	}
}

bool KeyPressEvent::pressed(sf::Keyboard::Key key) {
	for (auto it = m_vKeyPressed.begin(); it != m_vKeyPressed.end(); ++it) {
		if (it->first == key) {
			return it->second;
		}
	}
	return false;
}

void KeyPressEvent::update(sf::Keyboard::Key key, bool isPressed) {
	//Update bool

	//Iterate through keys
	for (auto it = m_vKeyPressed.begin(); it != m_vKeyPressed.end(); ++it) {
		if (it->first == key) {
			it->second = isPressed;			//Set key is pressed/released
		}
	}
	/*
	switch (key)
	{
	//WASD
	case sf::Keyboard::A:
		bA = isPressed;
		break;
	case sf::Keyboard::D:
		bD = isPressed;
		break;
	case sf::Keyboard::S:
		bS = isPressed;
		break;
	case sf::Keyboard::W:
		bW = isPressed;
		break;

	//Arrow Keys
	case sf::Keyboard::Left:
		bLeft = isPressed;
		break;
	case sf::Keyboard::Right:
		bRight = isPressed;
		break;
	case sf::Keyboard::Up:
		bUp = isPressed;
		break;
	case sf::Keyboard::Down:
		bDown = isPressed;
		break;

	case sf::Keyboard::Escape:
		bEscape = isPressed;
		break;
	case sf::Keyboard::Space:
		bSpace = isPressed;
		break;
	case sf::Keyboard::LShift:
		bLeftShift = isPressed;
	default:
		break;
	}
	*/

}
