#include "KeyPressEvent.h"
#include <iostream>
KeyPressEvent::KeyPressEvent() {

}

void KeyPressEvent::update(sf::Keyboard::Key key, bool isPressed) {
	//Update bool
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

	default:
		break;
	}
}
