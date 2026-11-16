#ifndef BALLOON_H
#define BALLOON_H

#include <iostream>
#include "vector2D.h"
#include "rectangle.h"
#include "texture.h"
#include "mobileObject.h"

constexpr const int ANIMATION_RATE = 100;

class Balloon : public mobileObject {
private:
	int color;

	bool exploded;

	int animationFrame;

public:
	Balloon(const Rectangle& rect, const Vector2D<float>& vel, int color, Texture* texture);

	bool hit(const Rectangle& obj);

	void render() const override;

	bool update(float deltaTime) override;
};

#endif