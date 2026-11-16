#ifndef BUTTERFLY_H
#define BUTTERFLY_H

#include <iostream>
#include "vector2D.h"
#include "rectangle.h"
#include "texture.h"
#include "mobileObject.h"
#include <random>

constexpr const float BUTTERFLY_SPEED = 0.2;

class Butterfly : public mobileObject {
private:
	int direction;

	bool shot;

	int animationFrame;

	void returnDir();

	std::mt19937_64 randomGenerator;

public:
	Butterfly(const Rectangle& rect, const Vector2D<float>& vel, int dir, Texture* texture);

	bool hit(const Rectangle& obj);

	void render() const override;

	bool update(float deltaTime) override;
};

#endif