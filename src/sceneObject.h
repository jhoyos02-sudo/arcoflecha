#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include "rectangle.h"
#include "gameObject.h"

class sceneObject : public gameObject
{
protected:
	Rectangle hitbox;

public:
	sceneObject(Rectangle h, Texture* text, Game* g) :gameObject(g, text), hitbox(h) {}

	void render() const override;
	bool update(float delta) override;
	bool hit(const Rectangle& obj) { return hitbox.hasIntersection(obj); }
};

#endif // SCENE_OBJECT_H

