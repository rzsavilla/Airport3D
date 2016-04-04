/*!	\class KeyPressSub
	\brief notifes KeyPressObservers
	Will notify KeyPressOberservers that are subscribed if KeyPressEvent is updated/changed
*/

#ifndef KEYPRESSSUB_H
#define KEYPRESSSUB_H

#include <vector>
#include "KeyPressObserver.h"
#include "KeyPressEvent.h"

class KeyPressSub {
	std::vector<KeyPressObserver*> observers;	//!< Records current observers to be notified
public:
	void attach(KeyPressObserver* observer); 	//!< Adds a observer that will be notified \param observer Pointer to observer
	void dettach(KeyPressObserver* observer);	//!< Removes observer from vector of current observers \param observer Point to observer to remove
	void notify(KeyPressEvent* updatedState);	//!< Notifies all Recorded observers that a key press event has occured \param updatedState Points to the updated key press event
};

#endif