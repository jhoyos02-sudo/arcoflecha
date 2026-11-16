#include "sceneObject.h"
void sceneObject::render() const
{texture->render(collider.to_sdl()); }

bool sceneObject::update(float)
{
	return true;
}