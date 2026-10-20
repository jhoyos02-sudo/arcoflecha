#include "arrow.h"

using namespace std;

Arrow::Arrow(Game* g, Rectangle hit, Vector2D<float> vel, Texture* text) {
	game = g;
	hitbox = hit;
	velocidad = vel;
	textura = text;
}

void
Arrow::render() const {
	textura->render(hitbox.to_sdl());
}

bool
Arrow::update(float delta) {
	bool keep = true;

	hitbox.move(velocidad * delta);

	if (hitbox.getTopLeftCorner().getX() + hitbox.getWidth() < game->WINDOW_WIDTH) {
		return false;
	}

	return keep;
}
