#include "mobileObject.h"

bool mobileObject::update(float delta)
{
	hitbox.move(velocidad * delta);
	return true;
}
