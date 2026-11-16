#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include "rectangle.h"
#include "gameObject.h"

class sceneObject : public gameObject
{
protected:
	Rectangle collider;

public:
	sceneObject(Rectangle collider, Texture* texture, Game* game) :gameObject(game, texture), collider(collider) {}

	void render() const override;
	bool update(float delta) override;
	bool hit(const Rectangle& obj) { return collider.hasIntersection(obj); }
};

#endif // SCENE_OBJECT_H

