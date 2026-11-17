#ifndef MOBILE_OBJECT_H
#define MOBILE_OBJECT_H

#include "sceneObject.h"
#include <vector>

class mobileObject : public sceneObject
{
protected:
	Vector2D<float> velocidad;

public:
	mobileObject(const Vector2D<float>& vel, Rectangle hit, Texture* text, Game* g) : sceneObject(hit, text, g), velocidad(vel) {}
	virtual void render() const override { sceneObject::render(); }

	virtual bool update(float delta) override;
};

#endif // MOBILE_OBJECT_H

