/*! \class KeyPressObserver
	\brief Interface class
	Inherited by classes that want to be notified if a key is pressed or released
*/

#ifndef KEYPRESSOBSERVER_H
#define KEYPRESSOBSERVER_H

#include "KeyPressEvent.h"

class KeyPressObserver {
public:
	virtual void keysUpdated(KeyPressEvent* state) = 0; //!< Pure virtual function
};

#endif