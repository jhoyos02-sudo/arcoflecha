#ifndef MOBILE_OBJECT_H
#define MOBILE_OBJECT_H

#include "sceneObject.h"
#include <vector>

class mobileObject : public sceneObject
{
protected:
	Vector2D<float> velocidad;

public:
	mobileObject(const Vector2D<float>& velocidad, Rectangle collider, Texture* texture, Game* game) : sceneObject(collider, texture, game), velocidad(velocidad) {}
	virtual void render() const override { sceneObject::render(); }

	virtual bool update(float delta) override;
};

#endif // MOBILE_OBJECT_H

