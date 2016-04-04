#include "KeyPressSub.h"

void KeyPressSub::attach(KeyPressObserver* observer) {
	observers.push_back(observer);
}
void KeyPressSub::dettach(KeyPressObserver* observer) {
	for (auto it = observers.begin(); it != observers.end(); ) {
		if (*it == observer) {
			delete *it;
			it = observers.erase(it);
		}
		else {
			++it;
		}
	}
}
void KeyPressSub::notify(KeyPressEvent* updatedState) {
	for (auto observer : observers) {
		observer->keysUpdated(updatedState);
	}
}