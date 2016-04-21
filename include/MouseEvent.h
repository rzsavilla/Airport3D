#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include <SFML/Window/Mouse.hpp>

class MouseEvent {
public:

public:
	MouseEvent();				//!< Constructor
	void update();				
	void updateMousePos();
};

#endif