#include "mobileObject.h"

bool mobileObject::update(float delta)
{
	collider.move(velocidad * delta);
	return true;
}
