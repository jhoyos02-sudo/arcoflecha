#include "baloon.h"

using namespace std;

bool 
Baloon::hit(const Rectangle& obj) {
	return hitbox.hasIntersection(obj);
}

void
Baloon::render() const {

}

bool
Baloon::update(float delta) {
	bool keep;

	return keep;
}
