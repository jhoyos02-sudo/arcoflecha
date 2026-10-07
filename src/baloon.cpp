#include "baloon.h"

using namespace std;

bool 
Baloon::hit(const Rectangle& obj) {
	return hitbox.hasIntersection(obj);
}
