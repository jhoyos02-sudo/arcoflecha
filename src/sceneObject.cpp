#include "sceneObject.h"

void sceneObject::render() const { textura->render(hitbox.to_sdl()); }

bool sceneObject::update(float) { return true; }
