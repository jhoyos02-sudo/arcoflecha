#ifndef BALLOON_H
#define BALLOON_H

#include <iostream>
#include "vector2D.h"
#include "rectangle.h"
#include "texture.h"
#include "mobileObject.h"

constexpr const int FRAMES_ANIMACION = 100;

class Balloon : public mobileObject {
private:
	int color;
	bool explotado;
	int frame;

public:
	Balloon(const Rectangle& h, const Vector2D<float>& vel, int c, Texture* text);

	bool hit(const Rectangle& obj);

	void render() const override;

	bool update(float delta) override;
};

#endif
