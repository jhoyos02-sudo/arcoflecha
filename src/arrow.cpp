#include "arrow.h"
#include "game.h"

Arrow::Arrow(Game* g, const Rectangle& hit, const Vector2D<float>& vel, Texture* text)
	: mobileObject(vel, hit, text, g) {}

void
Arrow::render() const {
	mobileObject::render();
}

bool
Arrow::update(float delta) {
	mobileObject::update(delta);

	game->checkCollision(Rectangle(hitbox.getTopLeftCorner() + Point2D<>(100, 0), .5, .5));

	return !((hitbox.getTopLeftCorner().getX() + hitbox.getWidth()) > Game::WINDOW_WIDTH);
}
