#include "arrow.h"
#include "game.h"

Arrow::Arrow(Game* game, const Rectangle& collider, const Vector2D<float>& velocidad, Texture* texture)
	: mobileObject(velocidad, collider, texture, game) {}

void
Arrow::render() const {
	mobileObject::render();
}


bool
Arrow::update(float deltaTime) {
	mobileObject::update(deltaTime);

	game->checkCollision(Rectangle(collider.getTopLeftCorner() + Point2D<>(100, 0), .5, .5));

	return !((collider.getTopLeftCorner().getX() + collider.getWidth()) > Game::WINDOW_WIDTH);
}