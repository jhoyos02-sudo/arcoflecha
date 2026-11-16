#pragma once
#include "vector2D.h"
#include "texture.h"
#include "rectangle.h"
#include "sceneObject.h"

constexpr float const SPEED = 0.5f;

class Bow : public sceneObject {
private:
	Vector2D<float> velocity;
	bool isArmed;
	bool shootArrow;
	int arrows;
	

public: 
	Bow(const Rectangle& collider, const Vector2D<float>& velocity, Texture* texture);	
	void handleEvent(const SDL_Event& event);
	void render() const override;
	Rectangle getCollider() const { return collider; }
	bool isBowArmed() const { return isArmed; }
	bool isShootingArrow() const { return shootArrow; }
	bool update(float deltaTime) override;
	void arrowShot();
	int getArrows() const { return arrows; }
	void loadArrows(int maxArrows) { arrows = maxArrows; }
};