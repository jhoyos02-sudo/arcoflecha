#ifndef BUTTERFLY_H
#define BUTTERFLY_H

#include <iostream>
#include "vector2D.h"
#include "rectangle.h"
#include "texture.h"
#include "mobileObject.h"
#include <random>

constexpr const float VEL_MARIPOSA = 0.2;

class Butterfly : public mobileObject {
private:
	std::mt19937_64 random;

	int direccion;
	bool muerto;
	int frame;

	void finGiro();

public:
	Butterfly(const Rectangle& hitbox, const Vector2D<float>& vel, int dir, Texture* text);

	bool hit(const Rectangle& obj);
	void render() const override;
	bool update(float delta) override;
};

#endif
